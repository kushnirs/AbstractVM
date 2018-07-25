/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:33:58 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/25 16:27:07 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include <sys/stat.h>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <stack>
#include <typeinfo> 
#include <stdio.h>
#include <cstdlib>
#include <memory>

enum	eOperandType 
{
   _int8,
   _int16,
   _int32,
   _float,
   _double
};

class IOperand 
{
	public:
		virtual int					getPrecision( void ) const = 0;
		virtual eOperandType		getType( void ) const = 0;
		virtual IOperand const *	operator+( IOperand const & rhs) const = 0 ;
		virtual IOperand const *	operator-( IOperand const & rhs) const = 0 ;
		virtual IOperand const *	operator*( IOperand const & rhs) const = 0 ;
		virtual IOperand const *	operator/( IOperand const & rhs) const = 0 ;
		virtual IOperand const *	operator%( IOperand const & rhs) const = 0 ;

		virtual std::string const & toString( void ) const = 0;

		virtual ~IOperand( void ) {}
};

#endif