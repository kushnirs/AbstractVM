/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 10:01:09 by sergee            #+#    #+#             */
/*   Updated: 2018/07/11 20:13:12 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

template < typename T>
Operand<T>::Operand(T & val, int pres, eOperandType t) : value(val), presicion(pres), type(t) {  }

template < typename T>
Operand<T>::Operand(Operand<T> & a) { *this = a; }

template < typename T>
Operand<T> & Operand<T>::operator = (Operand & arr)
{
	value = getValue();
	presicion = getPrecision();
	type = getType();
	return (*this);
}

template < typename T>
Operand<T>::~Operand( void ) {  }

template < typename T>
T 					Operand<T>::getValue(void) { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) { return(presicion); }

template < typename T>
eOperandType		Operand<T>::getType( void ) { return(type);}

template < typename T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs) {  }

template < typename T>
IOperand const *	Operand<T>::operator-( IOperand const & rhs) {  }

template < typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) {  }

template < typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) {  }

template < typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) {  }

template < typename T>
std::string const & Operand<T>::toString( void ) { return(std::to_string(value)); }
