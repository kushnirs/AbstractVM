/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/31 12:55:17 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

#include "IOperand.hpp"
#include "Operand.hpp"

class AbstarctVM
{
	private:
		std::stack<std::shared_ptr<const IOperand>>	avm;
		std::string									message;
		std::string									string;
		std::string									command;
		eOperandType								type;
		bool										ex;

		IOperand const *	createOperand(void) const;
		bool				parse_command(std::string str);
		void				parser(bool inp);
		void				parse_value(bool comment, std::vector<std::string> & tokens);
		void				apply_instr();

		void				read_std_in();
		int					read_file(std::string const &name);

		void	Push();
		void	Pop();
		void	Assert();
		void	Dump();
		void	Add();
		void	Sub();
		void	Mul();
		void	Div();
		void	Mod();
		void	Print();
		void	Empty();
		void	Stack_size();

	public:
		AbstarctVM();
		AbstarctVM(AbstarctVM const & a);
		~AbstarctVM(void);
		AbstarctVM & operator=(AbstarctVM const & rhs);

		void					start_vm(int ac, char **av);
		std::string 			getMesssage() const;
		std::string 			getString() const ;
		std::string 			getCommand() const ;
		eOperandType 			getType() const ;
		std::stack<std::shared_ptr<const IOperand>>	getStack() const;

};

# endif