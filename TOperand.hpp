/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:09:12 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 13:09:17 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include "IOperand.hpp"

#ifndef TOPERAND_HPP_DEFINED
    # define TOPERAND_HPP_DEFINED
    template<class T> class Operand;
    #include "OperandFactory.hpp"
# endif

template <class T>
class Operand : public IOperand {
    
    public: 
        Operand(void);
        Operand( T value );
        Operand( std::string str );
        Operand( Operand const & cpy );
        ~Operand( void );

        Operand &operator=(Operand const & rhs);

		int getPrecision() const; // Precision of the type of the instance
		eOperandType getType( void ) const; // Type of the instance

      	IOperand const * operator+( IOperand const &rhs ) const; // sum
		IOperand const * operator-( IOperand const &rhs ) const; //diff
		IOperand const * operator*( IOperand const &rhs ) const; // product
		IOperand const * operator/( IOperand const &rhs ) const; // quotient
		IOperand const * operator%( IOperand const &rhs ) const; // modulo
		std::string const & toString ( void ) const; // string representation

    protected:
        std::string _value;
};

#endif
