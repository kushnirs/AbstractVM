/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/31 13:30:05 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <iomanip>
#include <limits>
#include "IOperand.hpp"
#include "AVM.hpp"

extern int counter;

union t_val
{
	long int	Value32;
	float		floatValue;
	double		doubleValue;
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

		T					getValue(void) const;
		int					getPrecision( void ) const;
		eOperandType		getType( void ) const;

		IOperand const *	operator+( IOperand const & rhs) const;
		IOperand const *	operator-( IOperand const & rhs) const;
		IOperand const *	operator*( IOperand const & rhs) const;
		IOperand const *	operator/( IOperand const & rhs) const;
		IOperand const *	operator%( IOperand const & rhs) const;
		std::string const &	toString( void ) const;

		Operand(std::string str, int pres, eOperandType t);
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
		default :	a == 0 ? throw std::invalid_argument("remainder by 0") : 0;
			return (static_cast<int>(a) % static_cast<int>(b));
	}
}

template < typename K>
K	back_value(IOperand const & b)
{
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
Operand<T>::Operand(std::string str, int pres, eOperandType t) : precision(pres), type(t)
{
	t_val	tmp;
	try
	{
		switch (type)
		{
			case _int8 :
				tmp.Value32 = std::stoi(str);
				tmp.Value32 < std::numeric_limits<int8_t>::min() || tmp.Value32 > std::numeric_limits<int8_t>::max() ?
					throw std::invalid_argument("Overflow on a value(1)") : 0;
				value = static_cast<int8_t>(tmp.Value32);
				break;
			case _int16 :
				tmp.Value32 = std::stoi(str);
				tmp.Value32 < std::numeric_limits<int16_t>::min() || tmp.Value32 > std::numeric_limits<int16_t>::max() ?
					throw std::invalid_argument("Overflow on a value(1)") : 0;
				value = static_cast<int16_t>(tmp.Value32);
				break;
			case _int32 :
				tmp.Value32 = std::stoi(str);
				tmp.Value32 == std::numeric_limits<int32_t>::min() || tmp.Value32 == std::numeric_limits<int32_t>::max() ?
					throw std::invalid_argument("Overflow on a value(1)") : 0;
				value = tmp.Value32;
				break;
			case _float :
				tmp.floatValue = std::stof(str);
				tmp.floatValue == std::numeric_limits<float>::min() || tmp.floatValue == std::numeric_limits<float>::max() ?
					throw std::invalid_argument("Overflow on a value(1)") : 0;
				value = tmp.floatValue;
				break;
			case _double :
				tmp.doubleValue = std::stod(str);
				tmp.doubleValue == std::numeric_limits<double>::min() || tmp.doubleValue == std::numeric_limits<double>::max() ?
					throw std::invalid_argument("Overflow on a value(1)") : 0;
				value = tmp.doubleValue;
				break;
		}
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument("Overflow on a value(1)");
	}
}

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
	std::stringstream ss;
	eOperandType t = type < second.getType() ? second.getType() : type;
	try
	{
		switch (t)
		{
			case _int8 :
				tmp[0].Value32 = static_cast<int8_t>(value);
				tmp[1].Value32 = ::back_value<int8_t>(second);
				return (new Operand<int8_t>(std::to_string(::operation(tmp[0].Value32, tmp[1].Value32, equals)), 0, t));
			case _int16 :
				tmp[0].Value32 = static_cast<int16_t>(value);
				tmp[1].Value32 = ::back_value<int16_t>(second);
				return (new Operand<int16_t>(std::to_string(::operation(tmp[0].Value32, tmp[1].Value32, equals)), 0, t));
			case _int32 :
				tmp[0].Value32 = static_cast<int32_t>(value);
				tmp[1].Value32 = ::back_value<int32_t>(second);
				return (new Operand<int32_t>(std::to_string(::operation(tmp[0].Value32, tmp[1].Value32, equals)), 0, t));
			case _float :
				equals == '%' ? throw std::invalid_argument("can't % with float") : 0;
				tmp[0].floatValue = static_cast<float>(value);
				tmp[1].floatValue = ::back_value<float>(second);
				ss << ::operation(tmp[0].floatValue, tmp[1].floatValue, equals);
				return (new Operand<float>((ss.str()), (ss.str()).find(".") != std::string::npos ? (ss.str()).size() - (ss.str()).find(".") - 1 : 0, t));
			case _double :
				equals == '%' ? throw std::invalid_argument("can't % with double") : 0;
				tmp[0].doubleValue = static_cast<double>(value);
				tmp[1].doubleValue = ::back_value<double>(second);
				ss << ::operation(tmp[0].floatValue, tmp[1].floatValue, equals);
				return (new Operand<double>((ss.str()), (ss.str()).find(".") != std::string::npos ? (ss.str()).size() - (ss.str()).find(".") - 1 : 0, t));
		}
	}
	catch (std::exception & e)
	{
		std::cout << "avm: Line " << ::counter << " Error : " << e.what()<< std::endl;
		return (NULL);
	}
}

template < typename T>
T 					Operand<T>::getValue(void) const { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) const { return(precision); }

template < typename T>
eOperandType		Operand<T>::getType( void ) const { return(type);}

template < typename T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs) const {
	IOperand const *tmp = castType(rhs, '+');
	return(tmp ? tmp : NULL);
}

template < typename T>
IOperand const *	Operand<T>::operator-( IOperand const & rhs) const {
	IOperand const *tmp = castType(rhs, '-');
	return(tmp ? tmp : NULL);
}

template < typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) const {
	IOperand const *tmp = castType(rhs, '*');
	return(tmp ? tmp : NULL);
}

template < typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) const {
	IOperand const *tmp = castType(rhs, '/');
	return(tmp ? tmp : NULL);
}

template < typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) const {
	IOperand const *tmp = castType(rhs, '%');
	return(tmp ? tmp : NULL);
}

template < typename T>
std::string const & Operand<T>::toString( void ) const {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << (type == _int8 ? static_cast<int16_t>(value) : value);
	return(*(new std::string(ss.str())));
}

#endif