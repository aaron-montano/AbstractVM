/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:12:40 by amontano          #+#    #+#             */
/*   Updated: 2019/02/16 16:12:41 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <deque>
#include <stack>

template<typename T>
class MutantStack : public std::stack<T>
{
    public:

        typedef typename std::deque<T>::iterator iterator;

        MutantStack() {}
        MutantStack(MutantStack const &cpy) {
            *this = cpy;
        }
        ~MutantStack(void) {}

        MutantStack & operator=( MutantStack const &rhs) {
            this->std::stack<T>::operator=(rhs);
            return *this;
        }
        MutantStack<T>::iterator    begin(void) {
            return this->c.begin();
        }
        
        MutantStack<T>::iterator    end(void)   {
            return this->c.end();
        }
};

#endif
