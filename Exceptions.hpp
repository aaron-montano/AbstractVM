/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:31:44 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 15:31:47 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <exception>

struct AbstractVMExceptions {
    
    struct DivideByZeroException : public std::exception { 
        char const *what(void) const _NOEXCEPT;
    };
    struct OverflowException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct UnderflowException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct TooFewOperandsException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct UnknownOperationException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct AssertFalseException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct UnknownInstructionException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct InvalidValueException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct PopEmptyException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct PrintNotInt8Exception : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct FactoryOutOfBoundsException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct NoExitPointException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
    struct TooManyErrorsException : public std::exception {
        char const *what(void) const _NOEXCEPT;
    };
};
#endif