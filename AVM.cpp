/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:44 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/12 00:26:53 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVM.hpp"

AbstarctVM::AbstarctVM(std::stack<IOperand*> &st) : avm(st), string("") , val(NULL), command(""), type(_int8) { }

AbstarctVM::AbstarctVM(AbstarctVM const & a) : avm(a.avm) { *this = a; }

AbstarctVM::~AbstarctVM(void) { }

AbstarctVM & AbstarctVM::operator=(AbstarctVM const & rhs) {
	avm = rhs.getStack();
	string = rhs.getString();
	val = rhs.getVal();
	command = rhs.getCommand();
	type = rhs.getType();
	return (*this); }

std::string AbstarctVM::getString() const { return (string); }

IOperand* AbstarctVM::getVal() const { return (val); }

std::string AbstarctVM::getCommand() const { return (command); }

eOperandType AbstarctVM::getType() const { return (type); }

std::stack<IOperand*> AbstarctVM::getStack() const { return (avm); }

IOperand const * AbstarctVM::createOperand() const
{
	int val = std::stoi(string);
	switch (type)
	{
		case _int8 :
			return (new Operand<int8_t>(static_cast<int8_t>(val), 0, type));
		default :
			std::cout << "sobaka" << std::endl;
	}
	return (NULL);
}

void AbstarctVM::aply_instructions()
{
	IOperand const * lol = createOperand();
	if (command == "push")
		avm.push(const_cast<IOperand*>(lol));
	else
		std::cout << "lalka" << std::endl;
}

void AbstarctVM::parse_string(void)
{
	std::vector<std::string> 	tokens;
    std::istringstream			iss(string);
    std::string 				token;
    std::string					str1("push pop dump assert add sub mul div mod print exit");
    std::string					str3("0123456789.");


    if (string == ";;")
    	return;
    while (std::getline(iss, token, ' '))
    	tokens.push_back(token);
    if (tokens.size() != 2)
		throw std::invalid_argument("avm: instruction is unknown");
	else if (str1.find(tokens[0]) == std::string::npos || tokens[0].find(" ") != std::string::npos)
		throw std::invalid_argument("avm: wrong command");
	else
		command = tokens[0];

	size_t	iter = 0;
	size_t	iter2 = 0;
	if ((iter = tokens[1].find("(")) == std::string::npos ||
		(iter2 = tokens[1].find(")")) == std::string::npos || iter2 + 1 != tokens[1].size())
		throw std::invalid_argument("avm: wrong type");
	else
	{
		std::string t;
		t = tokens[1].substr(0, iter);
		if (t == "int8" )
			type = _int8;
		else if (t == "int16")
			type = _int16;
		else if (t == "int32")
			type = _int32;
		else if (t == "float")
			type = _float;
		else if (t == "double")
			type = _double;
		else
			throw std::invalid_argument("avm: wrong type");
	}
	string = tokens[1].substr(iter + 1, iter2 - iter - 1);

	int a = 0;
	for (size_t i = 0; i < string.length(); i++)
	{
		string[i] == '.' ? a++ : 0;
		if (str3.find(string[i]) == std::string::npos || a == 2)
			throw std::invalid_argument("avm: wrong symbol in number");
	}
	aply_instructions();
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
		throw std::invalid_argument("avm: No such file or directory");
	if (stat(name.c_str(), &ifreg) == -1)
		throw std::invalid_argument("avm: Is a directory");
	if (!(ifreg.st_mode & S_IFREG))
		throw std::invalid_argument("avm: wrong stat");
	str << file.rdbuf();
	string =  str.str();
	file.close();
	parse_string();
	return (-1);
}
