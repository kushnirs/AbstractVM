/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/20 17:11:51 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

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
		bool					exit;

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