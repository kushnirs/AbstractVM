/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/12 12:58:04 by skushnir         ###   ########.fr       */
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
		std::string		res;
	public:
		T 					getValue(void);
		int					getPrecision( void ) const;
		eOperandType		getType( void ) const;
		IOperand const *	operator+( IOperand const & rhs) const;
		IOperand const *	operator-( IOperand const & rhs) const;
		IOperand const *	operator*( IOperand const & rhs) const;
		IOperand const *	operator/( IOperand const & rhs) const;
		IOperand const *	operator%( IOperand const & rhs) const;
		std::string const & toString( void ) const;
		Operand(T && val, int pres, eOperandType t);
		Operand(Operand<T> & a);
		~Operand( void );
		Operand<T> & operator = (Operand & arr);
};

template < typename T>
Operand<T>::Operand(T && val, int pres, eOperandType t) : value(val), presicion(pres), type(t), res(std::to_string(value)) {  }

template < typename T>
Operand<T>::Operand(Operand<T> & a) { *this = a; }

template < typename T>
Operand<T> & Operand<T>::operator = (Operand & arr)
{
	value = arr.getValue();
	presicion = arr.getPrecision();
	type = arr.getType();
	res = std::to_string(value);
	return (*this);
}

template < typename T>
Operand<T>::~Operand( void ) {  }

template < typename T>
T 					Operand<T>::getValue(void) { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) const { return(presicion); }

template < typename T>
eOperandType		Operand<T>::getType( void ) const { return(type);}

template < typename T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs) const {return(&rhs);}

template < typename T>
IOperand const *	Operand<T>::operator-( IOperand const & rhs) const { return (&rhs); }

template < typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) const { return (&rhs); }

template < typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) const { return (&rhs); }

template < typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) const { return (&rhs); }

template < typename T>
std::string const & Operand<T>::toString( void ) const { return(res); }

#endif