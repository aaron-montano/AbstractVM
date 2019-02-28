/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 08:40:49 by amontano          #+#    #+#             */
/*   Updated: 2019/02/17 08:40:50 by amontano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

void usage()
{
	std::cout << "usage: ./avm [-vc] [file]" << std::endl;
}

bool parseArgs(int ac, char **av, char **file, char **options)
{
	std::regex reg_option("^-(?:c|v)+");
	struct stat st;
	
	for (int i = 1; i < ac; i++) {
		if (!*options &&  av[i][0] == '-') {
			*options = av[i];
			if (!std::regex_search(*options, reg_option)) {
				usage();
				return false;
			}
		}
		else if (!*file)
			*file = av[i];
	}
	if (*file) {
		std::ifstream infile(*file);
		if (stat(*file, &st) != 0) {
			std::cout   << BOLDRED << "avm: " << BOLDWHITE <<  *file << ": No such file or directory" << RESET << std::endl;
			return false;
		}
		else if (!infile) {
			std::cout << BOLDRED << "avm: " << BOLDWHITE << *file << ": Permission denied" << RESET << std::endl;
			return false;
		}
		else if (st.st_mode & S_IFDIR) {
			std::cout << BOLDRED << "avm: " << BOLDWHITE << *file << ": Is a directory" << RESET << std::endl;
			return false;
		}
		infile.close();
	}
	return (true);
 }

int main(int argc, char **argv)
{
	Lexer lex;
	char *file = nullptr;
	char *options = nullptr;

	try {
		if (argc == 2 || argc == 3)	{
			lex.status = parseArgs(argc, argv, &file, &options);
			if (!lex.status)
				exit(1);
		}
		if (file)
			lex.status = lex.fromInfile(file);
		else
			lex.status = lex.fromStdin();
		if (!lex.status)
			exit(1);
		if (argc < 4) {
			Calc *rpc = new Calc();
			if (options) {
				rpc->verbose = (std::string(options).find('v') != std::string(options).std::string::npos);
				rpc->cont_on_err = (std::string(options).find('c') != std::string(options).std::string::npos);
			}
			std::deque<std::string>::iterator i = lex._commands->begin();
			std::deque<std::string>::iterator end = lex._commands->end();
			for (; i != end; i++) {
				rpc->status = rpc->call(lex._commands->front());
				lex._commands->pop_front();
				if (!rpc->status)
					break;
			}
			delete rpc;
		}
		else {
			usage();
			exit(1);
		}
	}
	catch (std::exception &e) {
		std::cout << BOLDRED << "Error: " << BOLDWHITE << e.what() << RESET << std::endl;
	}
	return 0;
}
