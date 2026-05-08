/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 14:45:39 by ypacileo          #+#    #+#             */
/*   Updated: 2026/05/07 16:06:40 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>

class BitcoinExchange
{
	private:
	
	std::map<std::string, std::string>mapData;
	std::map<std::string, std::string>mapInput;

	public:
	typedef typename std::map<std::string, std::string>::iterator iterator;
	BitcoinExchange();
	~BitcoinExchange();
	bool isDatevaild(const std::string &date);
	iterator searchDate(const std::string &date);
	void uploadfile(const std::string &fileName, std::map<std::string, std::string>&map, char delim);
	void printBtc(const std::string &dataBase, const std::string &fileInput);
};

#endif