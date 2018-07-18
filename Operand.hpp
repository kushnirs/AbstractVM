/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:21:40 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/18 07:47:29 by sergee           ###   ########.fr       */
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
		Operand<T>	const	&	castType(IOperand const *tmp, eOperandType t) const;
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

// template < typename T>
// Operand<T>	const	&	Operand<T>::castType(IOperand const *tmp, eOperandType t) const
// {
// 	try
// 	{
// 		switch (t)
// 		{
// 			case _int8 : return (dynamic_cast<const Operand<int8_t>&>(*tmp));
// 			case _int16 : return (dynamic_cast<const Operand<int16_t>&>(*tmp));
// 			case _int32 : return (dynamic_cast<const Operand<int32_t>&>(*tmp));
// 			case _float : return (dynamic_cast<const Operand<float>&>(*tmp));
// 			case _double : return (dynamic_cast<const Operand<double>&>(*tmp));
// 		}
// 	}
// 	catch (std::exception & e)
// 	{
// 		throw std::invalid_argument("bad cast");
// 	}
// }

template < typename T>
T 					Operand<T>::getValue(void) { return(value); }

template < typename T>
int					Operand<T>::getPrecision( void ) const { return(presicion); }

template < typename T>
eOperandType		Operand<T>::getType( void ) const { return(type);}

template < typename T>
IOperand const *	Operand<T>::operator+( IOperand const & rhs) const
{
		// if (type < rhs.getType())
		// {
		// 	// dynamic_cast<IOperand>(*this);
		// 	Operand<T> const &tmp1 = castType(&rhs, rhs.getType());
		// 	// Operand<T> &tmp2 = castType(rhs);
		// }
		return (&rhs);
}

template < typename T>
IOperand const *	Operand<T>::operator-( IOperand const & rhs) const
{
	return (&rhs);
}

template < typename T>
IOperand const *	Operand<T>::operator*( IOperand const & rhs) const
{
	return (&rhs);
}

template < typename T>
IOperand const *	Operand<T>::operator/( IOperand const & rhs) const
{
	return (&rhs);
}

template < typename T>
IOperand const *	Operand<T>::operator%( IOperand const & rhs) const
{
	return (&rhs);
}

template < typename T>
std::string const & Operand<T>::toString( void ) const { std::string *tmp = new std::string(std::to_string(value)); return(*tmp); }

#endif