/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:10:36 by amontano          #+#    #+#             */
/*   Updated: 2019/02/15 18:42:20 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>
# include <iostream>
# include "Exceptions.hpp"

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {

	public:

		virtual ~IOperand() {}

		virtual int getPrecision() const = 0; // Precision of the type of the instance
		virtual eOperandType getType( void ) const = 0; // Type of the instance

		//public member functions
		virtual IOperand const * operator+( IOperand const &rhs ) const = 0; // sum
		virtual IOperand const * operator-( IOperand const &rhs ) const = 0; //diff
		virtual IOperand const * operator*( IOperand const &rhs ) const = 0; // product
		virtual IOperand const * operator/( IOperand const &rhs ) const = 0; // quotient
		virtual IOperand const * operator%( IOperand const &rhs ) const = 0; // modulo
		virtual std::string const & toString ( void ) const = 0; // string representation

	private:

};


#endif
