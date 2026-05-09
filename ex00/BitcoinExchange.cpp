/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:37:00 by ypacileo          #+#    #+#             */
/*   Updated: 2026/05/09 23:16:26 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange(const std::string &Database, char delim):_dataBase(Database), _delim(delim)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: mapData(other.mapData), _dataBase(other._dataBase), _delim(other._delim)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if(this != &other)
	{
		this->mapData = other.mapData;
		this->_dataBase = other._dataBase;
		this->_delim = other._delim;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}

static std::string trim(const std::string &str)
{
	size_t start;
	size_t end;

	start = 0;
	while (start < str.length() && std::isspace(str[start]))
		start++;
	end = str.length();
	while (end > start && std::isspace(str[end - 1]))
		end--;
	return (str.substr(start, end - start));
}

bool BitcoinExchange::isDateVaild(const std::string &date)
{
	int year;
	int month;
	int day;
	size_t i;
					//  0   1    2   3   4   5   6  7    8   9  10 11
	int days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	i = 0;
	while (i < date.length())
	{
		if (i != 4 && i != 7 && !std::isdigit(date[i]))
			return (false);
		i++;
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		days_month[1] = 29;
	if (day < 1 || day > days_month[month - 1])
		return (false);
	return (true);
}

double BitcoinExchange::parseValue(const std::string &value)
{
	std::stringstream ss;
	double number;
	char extra;
	std::string clean;

	clean = trim(value);
	ss.str(clean);
	ss >> number;
	if (ss.fail() || (ss >> extra))
		throw std::runtime_error("Error: bad input => " + clean);
	if (number < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (number > 1000)
		throw std::runtime_error("Error: too large a number.");
	return (number);
}

BitcoinExchange::iterator BitcoinExchange::searchDate(const std::string &date)
{
	iterator it;

	it = mapData.lower_bound(date);
	if (it != mapData.end() && it->first == date)
		return (it);
	if (it == mapData.begin())
		return (mapData.end());
	--it;
	return (it);
}

void BitcoinExchange::uploadfile()
{
    std::ifstream in(_dataBase.c_str());
	std::string line, date, value;
	bool headerSkipped = false;
	
    if (!in.is_open())
    	throw std::invalid_argument( "Error: could not open file.");

    while (std::getline(in, line))
    {
        if (line.empty()) continue;
		if (!headerSkipped && !isdigit(line[0])) 
		{
            headerSkipped = true;
            continue;
        }
        std::stringstream ss(line);
		if (std::getline(ss, date, _delim) && std::getline(ss, value))
        	mapData[date] = std::atof(value.c_str());
    }
    in.close();
}

void BitcoinExchange::printBtc(const std::string &date, const std::string &value)
{
	iterator itData;
	double number;
	std::string clean_date;

	try
	{
		clean_date = trim(date);
		if (!isDateVaild(clean_date))
		{
			std::cerr << "Error: bad input => " << clean_date << std::endl;
			return ;
		}
		number = parseValue(value);
		itData = searchDate(clean_date);
		if (itData == mapData.end())
		{
			std::cerr << "Error: bad input => " << clean_date << std::endl;
			return ;
		}
		std::cout << clean_date << " => " << number << " = "
				  << number * itData->second << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}