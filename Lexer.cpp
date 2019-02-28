/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:40:48 by amontano          #+#    #+#             */
/*   Updated: 2019/02/20 10:40:48 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include <fstream>
#include "Exceptions.hpp"
#include "Lexer.hpp"
#include <sstream>
#include <iostream>
#include "Colors.hpp"

Lexer::Lexer() : _commands(nullptr), status(true), _errnum(0) {}

Lexer::Lexer(Lexer const & cpy) : _commands(nullptr), status(true), _errnum(0)
{
	*this = cpy;
}

Lexer::~Lexer()
{
	std::deque<std::string>::iterator end = _commands->end();
	std::deque<std::string>::iterator i = _commands->begin();
	for (; i != end; i++)
		_commands->pop_front();
	delete _commands;
}

Lexer &Lexer::operator=(Lexer const &rhs)
{
	static_cast<void>(rhs);
	return *this;
}

bool Lexer::validLine(std::string line, bool *will_exit)
{
	std::regex reg_int("^\\s*(?:push|assert)\\s+int(?:8|16|32)\\(\\s*-??[0-9]+\\s*\\)\\s*$");
	std::regex reg_fp("^\\s*(?:push|assert)\\s+(?:float|double)\\(\\s*-??[0-9]+\\.([0-9]+)\\)\\s*$");
	std::regex reg_cmd("^\\s*(?:add|sub|mul|div|mod|pop|dump|print)\\s*$");
	std::regex reg_exit("^\\s*exit\\s*");
	std::regex reg_comm("^.*;.*$");
	std::regex reg_empty("^\\s*$");

	if (std::regex_search(line, reg_exit)) {
		*will_exit = true;
		return(true);
	}
	return (std::regex_search(line, reg_int)    | 
			std::regex_search(line, reg_fp)     | 
			std::regex_search(line, reg_cmd)    |
			std::regex_search(line, reg_comm)   |
			std::regex_search(line, reg_empty)  );
}

bool Lexer::fromInfile(std::string filename)
{
	std::ifstream infile;
	_commands = new std::deque<std::string>;
	infile.open(filename, std::ios::in | std::ios::out);
	std::string line;
	int	line_num = 1;
	bool will_exit = false;
	bool has_err = false;
	while (std::getline(infile, line))
	{
		if (_errnum >= 20)
			throw AbstractVMExceptions::TooManyErrorsException();
		std::istringstream iss(line);
		if (validLine(line, &will_exit))
			_commands->push_back(std::string(line));
		else {
			std::cout << BOLDRED << "Lexer:: " << BOLDWHITE << "Line " << line_num << ": Invalid : " << line << RESET << std::endl;
			has_err = true;
			_errnum += 1;
		}
		line_num++;
	}
	infile.close();
	if (!will_exit)
	{
		throw AbstractVMExceptions::NoExitPointException();
	}
	return (!has_err);
}

bool Lexer::fromStdin(void)
{
	_commands = new std::deque<std::string>;
	bool will_exit = false;
	bool has_err = false;
	int line_num = 1;
	std::string line;
	while (std::getline(std::cin, line)) {
		if (validLine(line, &will_exit))
			_commands->push_back(line);
		else {
			std::cout << BOLDRED << "Lexer:: " << BOLDWHITE << "Line " << line_num << ": Invalid : " << line << RESET << std::endl;
			has_err = true;
		}
		if (line.find(";;") != std::string::npos && \
			(line.find(";;") == line.find_first_of(';')) )
				break ;
		line_num++;
	}
	if (!will_exit)
		throw AbstractVMExceptions::NoExitPointException();
	return (!has_err);
}
