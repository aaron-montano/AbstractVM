/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 08:57:22 by amontano          #+#    #+#             */
/*   Updated: 2019/02/17 08:57:23 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "IOperand.hpp"

#ifndef OPERANDFACTORY_HPP_DEFINED
    # define OPERANDFACTORY_HPP_DEFINED
    class OperandFactory;
    #include "TOperand.hpp"
# endif

class OperandFactory {

    public:
        typedef IOperand const * (OperandFactory::*IOPCreatorFn)(std::string const &) const;
        OperandFactory();
        OperandFactory(OperandFactory const & cpy);
        ~OperandFactory();
        OperandFactory &operator=(OperandFactory const & rhs);
        
        IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    private:
        //factory methods
            IOperand const * createInt8 ( std::string const & value ) const;
            IOperand const * createInt16 ( std::string const & value ) const;
            IOperand const * createInt32 ( std::string const & value ) const;
            IOperand const * createFloat ( std::string const & value ) const;
            IOperand const * createDouble ( std::string const & value ) const;
};

#endif