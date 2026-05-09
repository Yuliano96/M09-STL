/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 14:45:39 by ypacileo          #+#    #+#             */
/*   Updated: 2026/05/09 22:46:36 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double> mapData;
		std::string _dataBase;
		char _delim;

	public:
		typedef std::map<std::string, double>::iterator iterator;

		BitcoinExchange(const std::string &dataBase, char delim);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		bool isDateVaild(const std::string &date);
		double parseValue(const std::string &value);
		iterator searchDate(const std::string &date);
		void uploadfile();
		void printBtc(const std::string &date, const std::string &value);
};

#endif