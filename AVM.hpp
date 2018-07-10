/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:42 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 14:02:52 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_HPP
# define AVM_HPP

#include <sys/stat.h>
#include <sstream>
#include <fstream>
#include "IOperand.hpp"

class AbstarctVM
{
	private:
		std::string	string;
		std::string	command;
		IOperand	*val;
		int			err(std::string const &str, int err_nb);
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