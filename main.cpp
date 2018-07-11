/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/11 11:23:02 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"

int main(int ac, char **av)
{
	std::stack<IOperand*> avm;
	AbstarctVM	cat(avm);

	try
	{
		while (cat.getString() != ";;")
		{
			
				if (ac == 1)
					cat.read_std_in();
				else if (ac > 2)
				{
					std::cout << "avm: too much arguments" << std::endl;
					return (-1);
				}
				else if (cat.read_file(av[1]))
					break;
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}