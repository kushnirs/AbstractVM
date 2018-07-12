/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/12 12:06:37 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"

int main(int ac, char **av)
{
	std::stack<IOperand*> avm;
	AbstarctVM	cat(avm);

	int counter = 1;
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
				counter++;
		}
	}
	catch (std::exception & e)
	{
		std::cout << "avm: " << "line " << counter << " Error : " << e.what() << std::endl;
	}
	return (0);
}