/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:44 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/20 00:10:24 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <unordered_map>
#include "AVM.hpp"

// Canonical form

AbstarctVM::AbstarctVM(std::stack<IOperand*> &st, std::string &msg) :
	avm(st), message(msg), string(""), command(""), type(_int8) { }

AbstarctVM::AbstarctVM(AbstarctVM const & a) :
	avm(a.avm), message(a.message) { *this = a; }

AbstarctVM::~AbstarctVM(void) { }

AbstarctVM & AbstarctVM::operator=(AbstarctVM const & rhs) {
	avm = rhs.getStack();
	string = rhs.getString();
	command = rhs.getCommand();
	type = rhs.getType();
	return (*this); }

// Canonical form


// Get func

std::string AbstarctVM::getMesssage() const { return (message); }

std::string AbstarctVM::getString() const { return (string); }

std::string AbstarctVM::getCommand() const { return (command); }

eOperandType AbstarctVM::getType() const { return (type); }

std::stack<IOperand*> AbstarctVM::getStack() const { return (avm); }

// Get func


// Operations

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

void AbstarctVM::Push() { avm.push(const_cast<IOperand*>(createOperand())); }

void AbstarctVM::Pop() {
	try
	{
		avm.pop();
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument("can't pop on empty stack");
	}
}

void AbstarctVM::Assert() {
	avm.empty() ? throw std::invalid_argument("can't assert on empty stack") : 0;
	IOperand * &tmp = avm.top();
	std::string const & str = tmp->toString();
	type != tmp->getType() || string != str ?
		throw std::invalid_argument("assert instruction is not true") : 0;
	delete &str;
}

void AbstarctVM::Dump() {
	avm.empty() ? throw std::invalid_argument("can't dump on empty stack") : 0;
	std::stack<IOperand*> tmp = avm;
	while(!tmp.empty())
	{
		IOperand * pointer = tmp.top();
		std::string const & str = pointer->toString();
		message.append(str);
		message += "\n";
		delete &str;
		tmp.pop();
	}	
}

void AbstarctVM::Add() {
	avm.size() != 2 ? throw std::invalid_argument("in stack < 2 numbers") : 0;
	std::stack<IOperand*> tmp = avm;
	tmp.pop();
	IOperand const *lol1 = *(avm.top()) + *(tmp.top());
	avm.pop();
	avm.pop();
	avm.push(const_cast<IOperand*>(lol1));
}

void AbstarctVM::Sub() {
	avm.size() != 2 ? throw std::invalid_argument("in stack < 2 numbers") : 0;
	std::stack<IOperand*> tmp = avm;
	tmp.pop();
	IOperand const *lol1 = *(avm.top()) - *(tmp.top());
	avm.pop();
	avm.pop();
	avm.push(const_cast<IOperand*>(lol1));
}

void AbstarctVM::Mul() {
	avm.size() != 2 ? throw std::invalid_argument("in stack < 2 numbers") : 0;
	std::stack<IOperand*> tmp = avm;
	tmp.pop();
	IOperand const *lol1 = *(avm.top()) * *(tmp.top());
	avm.pop();
	avm.pop();
	avm.push(const_cast<IOperand*>(lol1));
}

void AbstarctVM::Div() {
	avm.size() != 2 ? throw std::invalid_argument("in stack < 2 numbers") : 0;
	std::stack<IOperand*> tmp = avm;
	tmp.pop();
	IOperand const *lol1 = *(avm.top()) / *(tmp.top());
	avm.pop();
	avm.pop();
	avm.push(const_cast<IOperand*>(lol1));
}

void AbstarctVM::Print() {
	avm.empty() ? throw std::invalid_argument("can't assert on empty stack") : 0;
	IOperand * &tmp = avm.top();
	std::string a = tmp->toString();
	tmp->getType() == _float || tmp->getType() == _double || stoi(a) < 0 || stoi(a) > 255  ?
		throw std::invalid_argument("assert instruction is not true") : 0;
	message += static_cast<char>(stoi(a));
	message += "\n";
}

// Operations


// Parser

void AbstarctVM::apply_instr()
{
	std::string	str_action[9] =	{ "push", "pop", "assert", "dump", "add", "sub", "mul", "div", "print"};
	void (AbstarctVM::*action[9])() =
	{
		&AbstarctVM::Push, &AbstarctVM::Pop, &AbstarctVM::Assert, &AbstarctVM::Dump,
		&AbstarctVM::Add, &AbstarctVM::Sub, &AbstarctVM::Mul, &AbstarctVM::Div, &AbstarctVM::Print
	};
	for (int i = 0; i < 9; i++)
		if (str_action[i] == command)
			(this->*action[i])();
}

bool	AbstarctVM::parse_command(std::string str)
{
    std::string	str1("push pop dump assert add sub mul div mod print exit");
    size_t		iter;
    bool 		comment = (iter = str.find(";")) == std::string::npos ? 0 : 1;
    str = str.substr(0,iter);
	str1.find(str) == std::string::npos || ((str == "push" || str == "assert") && comment) ?
		throw std::invalid_argument("wrong command") : 0;
	command = str;
	return (comment);
}

void	AbstarctVM::parse_value(bool comment, std::vector<std::string> & tokens)
{
    std::string					str3("0123456789.");

	if (command != "push" && command != "assert")
    	!comment && tokens.size() > 1 && tokens[1][0] != ';' ?
    		throw std::invalid_argument("instruction is unknown") : 0;
    else
	{
		size_t	iter = 0;
		size_t	iter2 = 0;
		((iter = tokens[1].find("(")) == std::string::npos ||
		(iter2 = tokens[1].find(")")) == std::string::npos ||
		(tokens[1][iter2 + 1] != ';' && tokens.size() > 2 && tokens[2][0] != ';'))  ? 
			throw std::invalid_argument("instruction is unknown(1)") : 0;

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
}

void AbstarctVM::parser(bool inp)
{
	std::vector<std::string> 	tokens;
    std::istringstream			iss(string);
    std::string 				token;

    string == ";;" && !inp ? throw std::invalid_argument("illegal ;;") : 0;
    exit && inp && string != ";;" ? throw std::invalid_argument("after 'exit' command must be ';;' command") : 0;
    exit && !inp ? throw std::invalid_argument("after 'exit' command mustn't be another one") : 0;
    if (string == "" || string[0] == ';')
    	return;
    while (std::getline(iss, token, ' '))
    	tokens.push_back(token);
	parse_value(parse_command(tokens[0]), tokens);
	if (command == "exit")
		exit = true;
	apply_instr();
}

// Parser


// Read instr

void AbstarctVM::read_std_in()
{
	std::getline(std::cin, string);
	parser(true);
}

int AbstarctVM::read_file(std::string const &name){
    std::string 		token;
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
	token =  str.str();
    std::istringstream	iss(token);
	file.close();
	while (std::getline(iss, string, '\n'))
		parser(false);
	!exit ? throw std::invalid_argument("can't finish without 'exit' command") : 0;
	return (-1);
}

// Read instr