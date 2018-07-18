/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:44 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/13 17:03:24 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVM.hpp"

AbstarctVM::AbstarctVM(std::stack<IOperand*> &st, std::string &msg) : avm(st), message(msg), string(""), command(""), type(_int8) { }

AbstarctVM::AbstarctVM(AbstarctVM const & a) : avm(a.avm), message(a.message) { *this = a; }

AbstarctVM::~AbstarctVM(void) { }

AbstarctVM & AbstarctVM::operator=(AbstarctVM const & rhs) {
	avm = rhs.getStack();
	string = rhs.getString();
	command = rhs.getCommand();
	type = rhs.getType();
	return (*this); }

std::string AbstarctVM::getMesssage() const { return (message); }

std::string AbstarctVM::getString() const { return (string); }

std::string AbstarctVM::getCommand() const { return (command); }

eOperandType AbstarctVM::getType() const { return (type); }

std::stack<IOperand*> AbstarctVM::getStack() const { return (avm); }

IOperand const * AbstarctVM::createOperand() const
{
	try
	{
		switch (type)
		{
			case _int8 :
			{
				int res = std::stoi(string); res < -127 || res > 127 ?
					throw std::invalid_argument("Overflow on a value") : 0;
				return (new Operand<int8_t>(static_cast<int8_t>(res), 0, type));
			}
			case _int16 :
			{
				int res = std::stoi(string); res < -32768 || res > 32767 ?
					throw std::invalid_argument("Overflow on a value") : 0;
				return (new Operand<int16_t>(static_cast<int16_t>(res), 0, type));
			}
			case _int32 : return (new Operand<int32_t>(static_cast<int32_t>(std::stoi(string)), 0, type));
			case _float : return (new Operand<float>(std::stof(string.c_str(), NULL), 0, type));
			case _double : return (new Operand<double>(std::stod(string), 0, type));
		}
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument("Overflow on a value");
	}
}

void AbstarctVM::apply_instructions()
{
	if (command == "push")
		avm.push(const_cast<IOperand*>(createOperand()));
	else if (command == "pop")
	{
		try
		{
			avm.pop();
		}
		catch (std::exception & e)
		{
			throw std::invalid_argument("can't pop on empty stack");
		}
	}
	else if (command == "assert")
	{
		avm.empty() ? throw std::invalid_argument("can't assert on empty stack") : 0;
		IOperand * &tmp = avm.top();
		std::string const & str = tmp->toString();
		type != tmp->getType() || string != str ?
			throw std::invalid_argument("assert instruction is not true") : 0;
		delete &str;
	}
	else if (command == "dump")
	{
		avm.empty() ? throw std::invalid_argument("can't dump on empty stack") : 0;
		std::stack<IOperand*> tmp = avm;
		while(!tmp.empty())
		{
			IOperand * pointer = tmp.top();
			std::string const & str = pointer->toString();
			// std::cout << str << std::endl;
			message.append(str);
			delete &str;
			tmp.pop();
		}

			
	}
}

void AbstarctVM::parse_string(void)
{
	std::vector<std::string> 	tokens;
    std::istringstream			iss(string);
    std::string 				token;
    std::string					str1("push pop dump assert add sub mul div mod print exit");
    std::string					str3("0123456789.");


    if (string == ";;" || string == "")
    	return;

    while (std::getline(iss, token, ' '))
    	tokens.push_back(token);
	str1.find(tokens[0]) == std::string::npos || tokens[0].find(" ") != std::string::npos ?
		throw std::invalid_argument("wrong command") : 0;
	command = tokens[0];

	if (command != "push" && command != "assert")
    	tokens.size() != 1 ? throw std::invalid_argument("instruction is unknown") : 0;
    else
	{
		tokens.size() != 2  ?	throw std::invalid_argument("instruction is unknown") : 0;
		size_t	iter = 0;
		size_t	iter2 = 0;
		((iter = tokens[1].find("(")) == std::string::npos ||
		(iter2 = tokens[1].find(")")) == std::string::npos ||
		iter2 + 1 != tokens[1].size()) ? 
			throw std::invalid_argument("error ()") : 0;

		std::string tmp;
		tmp = tokens[1].substr(0, iter);
		if (tmp == "int8" )
			type = _int8;
		else if (tmp == "int16")
			type = _int16;
		else if (tmp == "int32")
			type = _int32;
		else if (tmp == "float")
			type = _float;
		else if (tmp == "double")
			type = _double;
		else
			throw std::invalid_argument("wrong type(1)");
		string = tokens[1].substr(iter + 1, iter2 - iter - 1);

		int a = 0;
		for (size_t i = 0; i < string.length(); i++)
		{
			string[i] == '.' ? a++ : 0;
			if (string[0] == '.' || str3.find(string[i]) == std::string::npos || a == 2)
				throw std::invalid_argument("wrong symbol in number");
		}
		a && (type == _int8 || type == _int16 || type == _int32) ? throw std::invalid_argument("discrepancy type with number") : 0;
	}

	apply_instructions();
}


void AbstarctVM::read_std_in()
{
	std::getline(std::cin, string);
	parse_string();
}

int AbstarctVM::read_file(std::string const &name){
	struct stat			ifreg;
	std::stringstream	str;

	std::ifstream file(name);
	if (!file.is_open() || !file.good())
		throw std::invalid_argument("No such file or directory");
	if (stat(name.c_str(), &ifreg) == -1)
		throw std::invalid_argument("Is a directory");
	if (!(ifreg.st_mode & S_IFREG))
		throw std::invalid_argument("wrong stat");
	str << file.rdbuf();
	string =  str.str();
	file.close();
	parse_string();
	return (-1);
}
