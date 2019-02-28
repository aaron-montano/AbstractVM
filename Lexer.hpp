/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:08:04 by amontano          #+#    #+#             */
/*   Updated: 2019/02/20 12:08:05 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

#include "AbstractVM.hpp"

class Lexer {

    public:
        Lexer();
        Lexer(Lexer const & cpy);
        ~Lexer();

        Lexer &operator=(Lexer const &rhs);
        std::deque<std::string> *_commands;
        bool status;
        bool fromInfile(std::string filename);
        bool fromStdin(void);
        bool validLine(std::string line, bool *will_exit);
        uint _errnum;
};
#endif
