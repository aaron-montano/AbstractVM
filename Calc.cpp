/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   result: 2019/02/16 16:18:48 by amontano          #+#    #+#             */
/*   Updated: 2019/02/27 19:15:33 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calc.hpp"
#include "Colors.hpp"

Calc::Calc(void) : verbose(false), cont_on_err(false), status(true)
{
	_dTab.insert(std::make_pair("pop", &Calc::pop));
	_dTab.insert(std::make_pair("dump", &Calc::dump));
	_dTab.insert(std::make_pair("print", &Calc::print));

	_types[0] = "int8";
	_types[1] = "int16";
	_types[2] = "int32";
	_types[3] = "float";
	_types[4] = "double";

	_opers[0] = "add";
	_opers[1] = "sub";
	_opers[2] = "mul";
	_opers[3] = "div";
	_opers[4] = "mod";
}

Calc::Calc(Calc const &cpy) : verbose(cpy.verbose), cont_on_err(cpy.cont_on_err), status(cpy.status)
{
	*this = cpy;
}

Calc::~Calc(void)
{
	MutantStack<IOperand const *>::iterator i;
	MutantStack<IOperand const *>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++)
		delete *i;
}

Calc &Calc::operator=(Calc const &rhs)
{
	static_cast<void>(rhs);
	return *this;
}

//Call will return cont_on_err if error and true on success or blank command
bool Calc::call(std::string cmd)
{
	static int line_num = 1;
	try {
		//simply erase everthing after a semicolon
		if (cmd.find(';') != std::string::npos)
			cmd.erase(cmd.find(';'), std::string::npos);
		//trim leading whitespace
		if (cmd.find_first_not_of(" \t") != 0)
			cmd.erase(0, cmd.find_first_not_of(" \t"));
		//trim trailing whitespace
		while (cmd.size() != 0 && cmd.find_last_of(" \t") == cmd.size() - 1)
			cmd.pop_back();
		//return true if empty command to continue without error
		if (cmd.size() == 0)
			return true;
		//exit
		if (cmd == "exit")
			return false;
		//pop dump print
		if (cmd == "pop" || cmd == "dump" || cmd == "print")
			(this->*_dTab[cmd])();
		//push
		else if (cmd.substr(0, 5) == "push ")
			this->push(cmd.substr(5, std::string::npos));
		//check for operations
		else if (std::find(_opers.begin(), _opers.end(), cmd) != _opers.end())
			doOperation(cmd);
		//handle assert
		else if (cmd.substr(0, 7) == "assert ")
			doAssert(cmd.substr(7, std::string::npos));
		else {
			if (this->verbose)
				std::cout << BOLDRED << "VERBOSE:: " << BOLDWHITE << "Line " << line_num << ": Error: Unknown instruction: " << cmd << RESET << std::endl;
			throw AbstractVMExceptions::UnknownInstructionException();
		}
		return (true);
	}
	catch (std::exception &e) {
		std::cerr << BOLDRED << "Error: " << e.what() << RESET << std::endl;
		return (this->cont_on_err);
	}
}

void Calc::push(std::string value)
{
	if (value.size() < 4)
		throw AbstractVMExceptions::InvalidValueException();
	//enforce the formatting of type(value)
	if (value.find('(') == std::string::npos)
		throw AbstractVMExceptions::InvalidValueException();
	// close parentheses must be the last char
	if (value.back() != ')')
		throw AbstractVMExceptions::InvalidValueException();
	//get rid of close parenth
	value.pop_back();
	//get position of open parentheses
	unsigned int open_parenth = value.find('(');
	//grab everything before the open parentheses
	std::string type_id = value.substr(0, open_parenth);
	//clear value of what we grabbed
	value.erase(value.begin(), value.begin() + open_parenth + 1);
	if (this->verbose)
		std::cout  << BOLDGREEN << "VERBOSE:: " << YELLOW << "Pushing " << RESET << type_id << '(' << value << ')' << std::endl;
	for (int i = Int8; i <= Double; i++) {
		if (type_id == _types[i]) {
			this->stack.push(_factory.createOperand(static_cast<eOperandType>(i), value));
			return;
		}
	}
	throw AbstractVMExceptions::InvalidValueException();
}

void Calc::pop(void)
{
	if (this->stack.size() < 1)
		throw AbstractVMExceptions::PopEmptyException();
	delete this->stack.top();
	this->stack.pop();
}

void Calc::dump(void)
{
	if (stack.empty())
		return ;
	MutantStack<IOperand const *>::iterator i;
	MutantStack<IOperand const *>::iterator end = this->stack.begin() - 1;
	for (i = this->stack.end() - 1; i != end; i--)
		std::cout << (*i)->toString() << std::endl;
}

void Calc::print(void)
{
	if (this->stack.size() < 1)
		throw AbstractVMExceptions::PrintNotInt8Exception();
	IOperand const *top = this->stack.top();
	if (top->getType() != Int8)
		throw AbstractVMExceptions::PrintNotInt8Exception();
	char c = std::stoi(top->toString());
	if (c > 32 && c < 127)
		std::cout << c << std::endl;
	else
		std::cout << RED <<  "Non-displayable character (" << std::stoi(top->toString()) << ')' << RESET << std::endl;
}

void Calc::doOperation(const std::string &cmd)
{
	if (this->stack.size() < 2)
		throw AbstractVMExceptions::TooFewOperandsException();
	IOperand const *rhs = this->stack.top();
	this->stack.pop();
	IOperand const *lhs = this->stack.top();
	this->stack.pop();
	IOperand const *result = nullptr;

	if (this->verbose) {
		std::cout << BOLDGREEN <<  "VERBOSE:: " << YELLOW << "Operation: " << cmd << ' ' << RESET << _types[lhs->getType()] \
		<< '(' << lhs->toString() << ") " << _types[rhs->getType()] << '(' \
		<< rhs->toString() << ')' << RESET << std::endl;
	}
	try {
		if 		(cmd == "add")	result = *lhs + *rhs;
		else if (cmd == "sub")	result = *lhs - *rhs;
		else if (cmd == "mul")	result = *lhs * *rhs;
		else if (cmd == "div")	result = *lhs / *rhs;
		else if (cmd == "mod")	result = *lhs % *rhs;
		else
			throw AbstractVMExceptions::UnknownInstructionException();
	} catch (AbstractVMExceptions &e) {
		delete lhs;
		delete rhs;
		throw e;
	}
	this->stack.push(result);
	delete lhs;
	delete rhs;
}

void Calc::doAssert(const std::string &value)
{
	if (this->stack.size < 1)
		throw AbstractVMExceptions::AssertFalseException();
	this->push(value);
	IOperand const *lhs = this->stack.top();
	this->stack.pop();
	IOperand const *rhs = this->stack.top();
	if (lhs->getType() != rhs->getType() || lhs->toString() != rhs->toString())
		throw AbstractVMExceptions::AssertFalseException();
	else if (this->verbose)
		std::cout << BOLDGREEN << "VERBOSE:: " << YELLOW << "Assert passed: " << RESET << lhs->toString() << " == " << rhs->toString() << std::endl;
	delete lhs;
}
