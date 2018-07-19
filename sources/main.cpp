/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/19 23:53:10 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"

int main(int ac, char **av)
{
	std::stack<IOperand*> 	stack;
	std::string				message;
	AbstarctVM				virt(stack, message);

	int counter = 1;
	try
	{
		std::string exit;
		while ((exit = virt.getString()) != ";;")
		{
			if (ac == 1)
				virt.read_std_in();
			else if (ac > 2)
			{
				std::cout << "avm: too much arguments" << std::endl;
				return (-1);
			}
			else if (virt.read_file(av[1]))
				break;
			counter++;
		}
		std::cout << message << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "avm: " << "line " << counter << " Error : " << e.what() << std::endl;
	}
	return (0);
}