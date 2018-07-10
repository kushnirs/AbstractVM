/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:44 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 18:09:38 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVM.hpp"

AbstarctVM::AbstarctVM(void) : string("") , val(NULL), command(""), type("") { }

AbstarctVM::AbstarctVM(AbstarctVM const & a) {
	*this = a;
}

AbstarctVM::~AbstarctVM(void){ }

AbstarctVM & AbstarctVM::operator=(AbstarctVM const & rhs){	val = rhs.getVal(); return (*this);}

IOperand* AbstarctVM::getVal() const { return (val); }
std::string AbstarctVM::getString() const { return (string); }

void AbstarctVM::parse_string(void)
{
	std::vector<std::string> 	tokens;
    std::istringstream			iss(string);
    std::string 				token;
    std::string					str1("push pop dump assert add sub mul div mod print exit");
    std::string					str2("int8 int16 int32 float double");


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
		type = tokens[1].substr(0, iter);
	if (str2.find(type) == std::string::npos || type.find(" ") != std::string::npos)
		throw std::invalid_argument("avm: wrong type");
	string = tokens[1].substr(iter + 1, iter2 - iter - 1);
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
