/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:18:44 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 16:18:45 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_HPP
#define CALC_HPP

#include "Exceptions.hpp"
#include "MutantStack.hpp"
#include "OperandFactory.hpp"
#include "TOperand.hpp"
#include <array>
#include <map>

class Calc
{
  public:
	typedef void (Calc::*pfunc)(void);

	Calc();
	Calc(Calc const &cpy);
	~Calc();
	Calc &operator=(Calc const &rhs);

	bool call(std::string cmd);
	bool verbose;
	bool cont_on_err;
	bool status;
	
  private:
	std::map<const std::string, pfunc>	_dTab;
	std::array<std::string, 5>			_types;
	std::array<std::string, 5>			_opers;
	OperandFactory 						_factory;
	MutantStack<IOperand const *>		stack;

	void push(std::string val);
	void pop(void);
	void dump(void);
	void print(void);
	void doOperation(const std::string &s);
	void doAssert(const std::string &s);
};

#endif
