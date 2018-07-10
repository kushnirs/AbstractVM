/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 12:21:14 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

template < typename T>
class Operand : public IOperand
{
	private:
		T				value;
		int				presicion;
		eOperandType	type;
	public:
		int					getPrecision( void );
		eOperandType		getType( void );
		IOperand const *	operator+( IOperand const & rhs);
		IOperand const *	operator-( IOperand const & rhs);
		IOperand const *	operator*( IOperand const & rhs);
		IOperand const *	operator/( IOperand const & rhs);
		IOperand const *	operator%( IOperand const & rhs);
		std::string const & toString( void );
		~Operand( void ) {}
	
		Operand<T> & operator = (Operand & arr);
		Operand<T> & operator [] (Operand const & arr);
		T & operator [] (unsigned int n);
		unsigned	size();
};

#endif