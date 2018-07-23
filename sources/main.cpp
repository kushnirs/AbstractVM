/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/23 17:43:06 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"

int	counter(1);

int main(int ac, char **av)
{
	std::stack<IOperand*> 	stack;
	std::string				message;
	AbstarctVM				virt(stack, message);

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
		std::cout << message;
	}
	catch (std::exception & e)
	{
		std::cout << "avm: " << "Line " << ::counter << " Error : " << e.what() << std::endl;
	}
	return (0);
}