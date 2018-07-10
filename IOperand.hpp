/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:33:58 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 12:34:34 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include <stdexcept>

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