/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 08:57:20 by amontano          #+#    #+#             */
/*   Updated: 2019/02/17 08:57:21 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory::OperandFactory()    {return;}
OperandFactory::OperandFactory(OperandFactory const & cpy)  { static_cast<void>(cpy); }
OperandFactory::~OperandFactory()   {return;}

OperandFactory 
&OperandFactory::operator=( OperandFactory const & rhs )
{
    if (this != &rhs)
        static_cast<void>(rhs);
    return *this;
}

IOperand const * 
OperandFactory::createInt8( std::string const & value ) const {
    return new Operand<int8_t>(std::stoi(value));
}

IOperand const * 
OperandFactory::createInt16 ( std::string const & value ) const {
    return new Operand<int16_t>(std::stoi(value));
}

IOperand const * 
OperandFactory::createInt32 ( std::string const & value ) const {
    return new Operand<int32_t>(std::stoi(value));
}
IOperand const * 
OperandFactory::createFloat ( std::string const & value ) const {
    return new Operand<float>(std::stof(value));
}
IOperand const * 
OperandFactory::createDouble ( std::string const & value ) const {
    return new Operand<double>(std::stod(value));
}

IOperand const * 
OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
    //dispatch table
    static IOPCreatorFn creators[5] = {
        &OperandFactory::createInt8,
        &OperandFactory::createInt16,
        &OperandFactory::createInt32,
        &OperandFactory::createFloat,
        &OperandFactory::createDouble
    };
    IOperand const * created = nullptr;
    try {
        IOPCreatorFn fn = creators[type];
        created = (this->*fn)(value);
    } catch (std::exception & e) {
        throw AbstractVMExceptions::FactoryOutOfBoundsException();
    }
    return (created);
}