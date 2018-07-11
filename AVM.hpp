/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/11 20:37:20 by sergee           ###   ########.fr       */
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
		std::string				string;
		IOperand				*val;
		std::string				command;
		eOperandType			type;
		void		parse_string();
	public:
		AbstarctVM(std::stack<IOperand*> &st);
		AbstarctVM(AbstarctVM const & a);
		~AbstarctVM(void);
		AbstarctVM & operator=(AbstarctVM const & rhs);

		IOperand*				getVal() const ;
		std::string 			getString() const ;
		std::string 			getCommand() const ;
		eOperandType 			getType() const ;
		std::stack<IOperand*>	getStack() const;

		void				read_std_in();
		int					read_file(std::string const &name);
		void				aply_instructions();
		IOperand const *	createOperand(void) const;
};

# endif