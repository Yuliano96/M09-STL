/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:37:00 by ypacileo          #+#    #+#             */
/*   Updated: 2026/05/06 21:24:40 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isDatevaild(const std::string &date)
{
    int year, month, day;
    std::string s_year, s_month, s_day;
    std::stringstream ss(date);

    if (!std::getline(ss, s_year, '-') || !std::getline(ss, s_month, '-') || 
        !std::getline(ss, s_day)) 
        	return false;
    
	year = std::atoi(s_year.c_str());
    month = std::atoi(s_month.c_str());
    day = std::atoi(s_day.c_str());

    if (year < 2009 || year > 2025) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

BitcoinExchange::iterator BitcoinExchange::searchDate(const std::string &date)
{
    iterator it = map.lower_bound(date);
    
    if (it != map.end() && it ->first == date)
        return it;
    else if(it == map.begin())
    {
        std::cerr<<"date not found\n";
        return map.end();
    }
    else
    {
        it--;
        return it;
    }
}

void BitcoinExchange::uploadfile(const std::string &filename)
{
    std::ifstream in(filename);
	std::string line, date, value;
	bool headerSkipped = false;
	
    if (!in.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    while (std::getline(in, line))
    {
        if (line.empty()) continue;
		if (!headerSkipped && !isdigit(line[0])) 
		{
            headerSkipped = true;
            continue;
        }
        std::stringstream ss(line);
		if (std::getline(ss, date, ',') && std::getline(ss, value))
        {
            if (isDatevaild(date))
            	map.insert(std::pair<std::string, std::string>(date, value));
            else 
            	std::cerr << "Error: invalid date => " << date << std::endl;
        }
    }
    in.close();

    // 3. MOSTRAR RESULTADOS
    // std::map<std::string, std::string>::iterator it;
    // for (it = map.begin(); it != map.end(); ++it)
    // {
    //     std::cout << it->first << " | " << it->second << std::endl;
    // }
}