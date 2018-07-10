/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVM.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:08:44 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 14:00:01 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVM.hpp"

AbstarctVM::AbstarctVM(void) : string("") , val(NULL) { }

AbstarctVM::AbstarctVM(AbstarctVM const & a) {
	*this = a;
}

AbstarctVM::~AbstarctVM(void){ }

AbstarctVM & AbstarctVM::operator=(AbstarctVM const & rhs){	val = rhs.getVal(); return (*this);}

IOperand* AbstarctVM::getVal() const { return (val); }
std::string AbstarctVM::getString() const { return (string); }

void parse_string(void)
{
	std::vector<std::string> words;

}

int AbstarctVM::err(std::string const &str, int err_nb)
{
	if (err_nb == -1)
		std::cout << "avm: "<< str << ": No such file or directory" << std::endl;
	else if(err_nb == -2)
		std::cout << "avm: "<< str << ": Is a directory" << std::endl;
	else
		std::cout << "wrong stat" << std::endl;
	return (-1);
}

void AbstarctVM::read_std_in()
{
	std::cin >> string;
	parse_string();
}

int AbstarctVM::read_file(std::string const &name){
	struct stat			ifreg;
	std::stringstream	str;

	std::ifstream file(name);
	if (!file.is_open() || !file.good())
		return (err(name, -1));
	if (stat(name.c_str(), &ifreg) == -1)
		return (err("", -2));
	if (!(ifreg.st_mode & S_IFREG))
		return (err(name, -3));
	str << file.rdbuf();
	string =  str.str();
	file.close();
	parse_string();
	return (0);
}
