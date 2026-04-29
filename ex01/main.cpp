/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 21:01:13 by yuliano           #+#    #+#             */
/*   Updated: 2026/04/29 21:27:01 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc == 2)
		{
			RPN rpn(argv[1]);
			std::cout<< rpn.RPN_calculation()<< std::endl;
		}
		else
			throw std::invalid_argument("Error: Invalid number of arguments");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}