/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/25 17:54:33 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iomanip>
#include <map>
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
class Operand : public IOperand
{
	private:
		T				value;
		int				precision;
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
		virtual ~Operand( void );
		Operand<T> & operator = (Operand & arr);
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

template < typename K>
K	back_value(IOperand const & b, K type)
{
	(void)type;
	switch (b.getType())
	{
		case _int8 : return (static_cast<K>(dynamic_cast< Operand<int8_t> const & >(b).getValue()));
		case _int16 : return (static_cast<K>(dynamic_cast< Operand<int16_t> const & >(b).getValue()));			
		case _int32 : return (static_cast<K>(dynamic_cast< Operand<int32_t> const & >(b).getValue()));			
		case _float : return (static_cast<K>(dynamic_cast< Operand<float> const & >(b).getValue()));			
		case _double : return (static_cast<K>(dynamic_cast< Operand<double> const & >(b).getValue()));
	}
}

template < typename T>
Operand<T>::Operand(T && val, int pres, eOperandType t) : value(val), precision(pres), type(t) {  }

template < typename T>
Operand<T>::Operand(Operand<T> & a) { *this = a; }

template < typename T>
Operand<T> & Operand<T>::operator = (Operand & arr)
{
	value = arr.getValue();
	precision = arr.getPrecision();
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
			tmp[1].Value8 = ::back_value(second, (int8_t)1);
			return (new Operand<int8_t>(::operation(tmp[0].Value8, tmp[1].Value8, equals), 0, t));
		case _int16 :
			tmp[0].Value16 = static_cast<int16_t>(value);
			tmp[1].Value16 = ::back_value(second, (int16_t)1);
			return (new Operand<int16_t>(::operation(tmp[0].Value16, tmp[1].Value16, equals), 0, t));
		case _int32 :
			tmp[0].Value32 = static_cast<int32_t>(value);
			tmp[1].Value32 = ::back_value(second, (int32_t)1);
			return (new Operand<int32_t>(::operation(tmp[0].Value32, tmp[1].Value32, equals), 0, t));
		case _float :
			equals == '%' ? throw std::invalid_argument("can't % with float") : 0;
			tmp[0].floatValue = static_cast<float>(value);
			tmp[1].floatValue = ::back_value(second, (float)1);
			return (new Operand<float>(::operation(tmp[0].floatValue, tmp[1].floatValue, equals), 0, t));
		case _double :
			equals == '%' ? throw std::invalid_argument("can't % with double") : 0;
			tmp[0].doubleValue = static_cast<double>(value);
			tmp[1].doubleValue = ::back_value(second, (double)1);
			return (new Operand<double>(::operation(tmp[0].doubleValue, tmp[1].doubleValue, equals), 0, t));
	}
}

template < typename T>
T 					Operand<T>::getValue(void) const { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) const { return(precision); }

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
std::string const & Operand<T>::toString( void ) const {
	// std::stringstream ss;
	// ss << std::fixed << std::setprecision(precision) << value;
	// std::map<eOperandType, const char *> flag({
	// 	{ _int8, "hhd"},
	// 	{ _int16, "hd"},
	// 	{ _int32, "d"},
	// 	{ _float, "g"},
	// 	{ _double, "g"},
	// })
	// char * str;
	// return(*(new std::string(std::to_string(value))));
	// std::shared_ptr<std::string> lol(new std::string(std::to_string(value)));
	// std::cout << *lol << std::endl;
	return(*(new std::string(std::to_string(value))));
}

#endif