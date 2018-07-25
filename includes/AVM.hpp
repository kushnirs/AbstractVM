/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/25 18:27:02 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

#include "IOperand.hpp"
#include "Operand.hpp"

class AbstarctVM
{
	private:
		std::stack<std::shared_ptr<const IOperand>>	&avm;
		std::string				&message;
		std::string				string;
		std::string				command;
		eOperandType			type;
		bool					ex;

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
		AbstarctVM(std::stack<std::shared_ptr<const IOperand>> &st, std::string &msg);
		AbstarctVM(AbstarctVM const & a);
		~AbstarctVM(void);
		AbstarctVM & operator=(AbstarctVM const & rhs);

		std::string 			getMesssage() const;
		std::string 			getString() const ;
		std::string 			getCommand() const ;
		eOperandType 			getType() const ;
		std::stack<std::shared_ptr<const IOperand>>	getStack() const;

		void				read_std_in();
		int					read_file(std::string const &name);
};

# endif