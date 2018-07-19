/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/19 20:53:18 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

#include <sys/stat.h>
#include <sstream>
#include <fstream>
#include "IOperand.hpp"
#include "Operand.hpp"

class AbstarctVM
{
	private:
		std::stack<IOperand*>	&avm;
		std::string				&message;
		std::string				string;
		std::string				command;
		eOperandType			type;

		void				parser(bool inp);
		bool				parse_command(std::string str);
		void				parse_value(bool comment, std::vector<std::string> & tokens);
		void				apply_instr();
		IOperand const *	createOperand(void) const;

		void	Push();
		void	Pop();
		void	Assert();
		void	Dump();
		void	Add();
		void	Sub();
		void	Mul();
		void	Div();
		void	Print();
	public:
		AbstarctVM(std::stack<IOperand*> &st, std::string &msg);
		AbstarctVM(AbstarctVM const & a);
		~AbstarctVM(void);
		AbstarctVM & operator=(AbstarctVM const & rhs);

		std::string 			getMesssage() const;
		std::string 			getString() const ;
		std::string 			getCommand() const ;
		eOperandType 			getType() const ;
		std::stack<IOperand*>	getStack() const;

		void				read_std_in();
		int					read_file(std::string const &name);
};

# endif