/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:48:27 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 15:48:29 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

char const * 
AbstractVMExceptions::DivideByZeroException::what(void) const _NOEXCEPT {
    return ("DIVIDE by ZERO error!");
}

char const *
AbstractVMExceptions::OverflowException::what(void) const _NOEXCEPT {
    return("Overflow error");
}

char const *
AbstractVMExceptions::UnderflowException::what(void) const _NOEXCEPT {
    return("Underflow error");
}

char const *
AbstractVMExceptions::TooFewOperandsException::what(void) const _NOEXCEPT {
    return("Too few Operands error");
}

char const *
AbstractVMExceptions::UnknownOperationException::what(void) const _NOEXCEPT {
    return("Unknown Operation error");
}

char const *
AbstractVMExceptions::AssertFalseException::what(void) const _NOEXCEPT {
    return("Failed Assertion error");
}

char const *
AbstractVMExceptions::UnknownInstructionException::what(void) const _NOEXCEPT {
    return("Unknown instruction error");
}

char const *
AbstractVMExceptions::InvalidValueException::what(void) const _NOEXCEPT {
    return("Invalid Value error");
}

char const *
AbstractVMExceptions::PopEmptyException::what(void) const _NOEXCEPT {
    return("Pop Empty Stack error");
}

char const *
AbstractVMExceptions::PrintNotInt8Exception::what(void) const _NOEXCEPT {
    return("Print not Int8 error");
}

char const *
AbstractVMExceptions::FactoryOutOfBoundsException::what(void) const _NOEXCEPT {
    return ("Factory failed to produce operand error");
}

char const *
AbstractVMExceptions::NoExitPointException::what(void) const _NOEXCEPT {
    return ("Program has no exit point");
}

char const *
AbstractVMExceptions::TooManyErrorsException::what(void) const _NOEXCEPT {
    return ("Stopped because too many errors encountered");
}