/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 15:40:13 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

#include <sys/stat.h>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "IOperand.hpp"

class AbstarctVM
{
	private:
		std::string	string;
		IOperand	*val;
		std::string	command;
		std::string	type;
		void		parse_string();
	public:
		AbstarctVM(void);
		AbstarctVM(AbstarctVM const & a);
		~AbstarctVM(void);
		AbstarctVM & operator=(AbstarctVM const & rhs);

		IOperand*	getVal() const ;
		std::string getString() const ;
		void		read_std_in();
		int			read_file(std::string const &name);
};

# endif