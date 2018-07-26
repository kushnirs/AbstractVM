/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:32:22 by skushnir          #+#    #+#             */
/*   Updated: 2018/07/26 12:54:28 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "AVM.hpp"

int	counter(1);

int main(int ac, char **av)
{
	AbstarctVM	virt;
	
	virt.start_vm(ac, av);
	// system("leaks avm");
	return (0);
}