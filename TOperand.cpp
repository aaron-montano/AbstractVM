/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:53:32 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 13:53:33 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOperand.hpp"


template<class T> Operand<T>::Operand( void ) { 
	this->_value = std::to_string(static_cast<T>(0)); 
}

template<class T> Operand<T>::Operand( Operand<T> const & cpy ) {
	*this = cpy;
}

template<class T> Operand<T>::~Operand( void ) {}

template<class T> Operand<T> & Operand<T>::operator=( Operand<T> const & rhs ) {   
	this->_value = rhs._value;
	return *this;
}

template<class T> Operand<T>::Operand( T value ) {
	this->_value = std::to_string(value);
}

template<class T> Operand<T>::Operand( std::string str ) { 
	this->_value = std::to_string(static_cast<T>(stod(str)));
}

template<class T> void addOverflow(T a, T b) {
	try {
		T sum = a + b;
		static_cast<void>(sum);
	} catch (std::exception &e) {
		T sum =  a + b;
		//there is only potential to overflow both operands have the same sign
		if ((a < 0) == (b < 0)) {
			if (a > 0 && sum <= 0)
				throw AbstractVMExceptions::OverflowException();
			else if (a < 0 && sum >= 0)
				throw AbstractVMExceptions::UnderflowException();
		}
	}
}

template<class T> void multOverflow(T a, T b) {   
	T max = std::numeric_limits<T>::max();
	T abs_a = (a < 0) ? -a : a;
	T abs_b = (b < 0) ? -b : b;
	if (abs_a > max/abs_b)
	{
		if ((a < 0) == (b < 0))
			throw AbstractVMExceptions::OverflowException();
		else
			throw AbstractVMExceptions::UnderflowException();
	}
}

template<class T> IOperand const * Operand<T>::operator+( IOperand const & rhs) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	long double lhs_value = stold(this->_value);
	long double rhs_value = stold(rhs.toString());

	eOperandType final_type = (this->getPrecision() < rhs.getPrecision())  ? rhs.getType() : this->getType();
	addOverflow<T>(lhs_value, rhs_value);
	OperandFactory *factory = new OperandFactory();
	IOperand const *ret = factory->createOperand(final_type, std::to_string(lhs_value + rhs_value));
	delete factory;
	return ret;
}

template<class T> IOperand const * Operand<T>::operator-( IOperand const & rhs) const {
	long double lhs_value = stold(this->_value);
	long double rhs_value = stold(rhs.toString());

	eOperandType final_type = (this->getPrecision() < rhs.getPrecision())  ? rhs.getType() : this->getType();
	addOverflow<T>(lhs_value, rhs_value * -1);
	OperandFactory *factory = new OperandFactory();
	IOperand const *ret = factory->createOperand(final_type,std::to_string(lhs_value - rhs_value));
	delete factory;
	return ret;
}

template<class T> IOperand const * Operand<T>::operator*( IOperand const & rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	long double lhs_value = stold(this->_value);
	long double rhs_value = stold(rhs.toString());
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision())  ? rhs.getType() : this->getType();
	multOverflow<T>(lhs_value, rhs_value);
	OperandFactory *factory = new OperandFactory();
	IOperand const * ret = factory->createOperand(final_type, std::to_string(lhs_value * rhs_value));
	delete factory;
	return ret;
}

template<class T> IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	long double lhs_value = stold(this->toString());
	long double rhs_value = stold(rhs.toString());

	if (rhs_value == 0)
		throw AbstractVMExceptions::DivideByZeroException();
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision())  ? rhs.getType() : this->getType();
	OperandFactory *factory = new OperandFactory();
	IOperand const * ret = factory->createOperand(final_type, std::to_string(lhs_value / rhs_value));
	delete factory;
	return ret;
}

template<class T> IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	long lhs_value = stol(this->toString());
	long rhs_value = stol(rhs.toString());

	if (rhs_value == 0)
		throw  AbstractVMExceptions::DivideByZeroException();
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->getType();
	OperandFactory *factory = new OperandFactory();
	IOperand const *ret = factory->createOperand(final_type, std::to_string(lhs_value % rhs_value));
	delete factory;
	return ret;
}

template<class T> std::string const & Operand<T>::toString( void ) const {
	return this->_value;
}

template<> int
Operand<int8_t>::getPrecision(void) const {
	return Int8;
}

template<> int
Operand<int16_t>::getPrecision(void) const {
	return Int16;
}

template<> int
Operand<int32_t>::getPrecision(void) const {
	return Int32;
}

template<> int
Operand<float>::getPrecision(void) const {
	return Float;
}

template<> int
Operand<double>::getPrecision(void) const {
	return Double;
}

template<> eOperandType
Operand<int8_t>::getType(void) const {
	return Int8;
}

template<> eOperandType
Operand<int16_t>::getType(void) const {
	return Int16;
}

template<> eOperandType
Operand<int32_t>::getType(void) const{
	return Int32;
}

template<> eOperandType
Operand<float>::getType(void) const {
	return Float;
}

template<> eOperandType
Operand<double>::getType(void) const {
	return Double;
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
