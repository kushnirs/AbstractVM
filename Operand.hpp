/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/19 14:31:04 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"

union t_val
{
	int8_t	Value8;
	int16_t	Value16;
	int32_t	Value32;
	float	floatValue;
	double	doubleValue;
};

template < typename T>
T	operation(T const & a, T const & b, char equals)
{
	switch (equals)
	{
		case '+':	return (b + a);
		case '-':	return (b - a);
		case '*':	return (b * a);
		case '/':	a == 0 ? throw std::invalid_argument("division by 0") : 0;
					return (b / a);
		default :	return (static_cast<int>(a) % static_cast<int>(b));
	}
}

template < typename T>
class Operand : public IOperand
{
	private:
		T				value;
		int				presicion;
		eOperandType	type;
	public:
		IOperand const *	castType(IOperand const & second, char equals) const;
		T 					getValue(void) const;
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
Operand<T>::Operand(T && val, int pres, eOperandType t) : value(val), presicion(pres), type(t) {  }

template < typename T>
Operand<T>::Operand(Operand<T> & a) { *this = a; }

template < typename T>
Operand<T> & Operand<T>::operator = (Operand & arr)
{
	value = arr.getValue();
	presicion = arr.getPrecision();
	type = arr.getType();
	return (*this);
}

template < typename T>
Operand<T>::~Operand( void ) {  }


template < typename T>
IOperand const *	Operand<T>::castType(IOperand const & second, char equals) const
{
	t_val tmp[2];
	eOperandType t = type < second.getType() ? second.getType() : type;
	switch (t)
	{
		case _int8 :
			tmp[0].Value8 = static_cast<int8_t>(value);
			tmp[1].Value8 = dynamic_cast<Operand<int8_t> const &>(second).getValue();
			return (new Operand<int8_t>(::operation(tmp[0].Value8, tmp[1].Value8, equals), 0, t));
		case _int16 :
			tmp[0].Value16 = static_cast<int16_t>(value);
			tmp[1].Value16 = dynamic_cast<Operand<int16_t> const &>(second).getValue();
			return (new Operand<int16_t>(::operation(tmp[0].Value16, tmp[1].Value16, equals), 0, t));
		case _int32 :
			tmp[0].Value32 = static_cast<int32_t>(value);
			tmp[1].Value32 = dynamic_cast<Operand<int32_t> const &>(second).getValue();
			return (new Operand<int32_t>(::operation(tmp[0].Value32, tmp[1].Value32, equals), 0, t));
		case _float :
			equals == '%' ? throw std::invalid_argument("can't % with float") : 0;
			tmp[0].floatValue = static_cast<float>(value);
			tmp[1].floatValue = dynamic_cast<Operand<float> const &>(second).getValue();
			return (new Operand<float>(::operation(tmp[0].floatValue, tmp[1].floatValue, equals), 0, t));
		case _double :
			equals == '%' ? throw std::invalid_argument("can't % with double") : 0;
			tmp[0].doubleValue = static_cast<double>(value);
			tmp[1].doubleValue = dynamic_cast<Operand<double> const &>(second).getValue();
			return (new Operand<double>(::operation(tmp[0].doubleValue, tmp[1].doubleValue, equals), 0, t));
	}
}

template < typename T>
T 					Operand<T>::getValue(void) const { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) const { return(presicion); }

template < typename T>
eOperandType		Operand<T>::getType( void ) const { return(type);}

template < typename T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs) const { return (castType(rhs, '+')); }

template < typename T>
IOperand const *	Operand<T>::operator-( IOperand const & rhs) const { return (castType(rhs, '-')); }

template < typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) const { return (castType(rhs, '*')); }

template < typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) const { return (castType(rhs, '/')); }

template < typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) const { return (castType(rhs, '%')); }

template < typename T>
std::string const & Operand<T>::toString( void ) const { std::string *tmp = new std::string(std::to_string(value)); return(*tmp); }

#endif