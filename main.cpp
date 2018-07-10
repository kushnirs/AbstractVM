/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/10 15:02:12 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "AVM.hpp"

int main(int ac, char **av)
{
	AbstarctVM	cat;

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