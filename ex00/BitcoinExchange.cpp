/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:37:00 by ypacileo          #+#    #+#             */
/*   Updated: 2026/05/01 17:37:04 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::uploadfile()
{
	std::map<std::string, std::string>::iterator it;

	std::string line;
	std::string date;
	std::string value;
	std::ifstream in("data.csv");
	if (!in.is_open())
	{
		std::cerr<<"Error: The file cannot be opened.\n";
	}

	std::getline(in, line);
	
	while(std::getline(in, line))
	{
		
		std::stringstream ss(line);
		std::getline(ss, date, ',');
		std::getline(ss,value);
		map.insert(std::make_pair(date,value));
		
	}

	for(it = map.begin(); it != map.end(); ++it)
	{
		std::cout<<it->first<<" | " <<it->second<<std::endl;
	}
}