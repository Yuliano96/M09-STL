/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:44:24 by yuliano           #+#    #+#             */
/*   Updated: 2026/05/09 23:15:05 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include "BitcoinExchange.hpp"



int main(int argc, char **argv)
{
    std::string line;
    
    if(argc != 2)
    {
        std::cerr<< "Error: Invalid number of arguments\n";
        return (1);
    }
    
    std::ifstream input(argv[1]);
    if(!input.is_open())
    {
        std::cerr<<"Error: could not open file\n";
        return (1);
    }
    try
    {
        BitcoinExchange btc("data.csv", ',');
        bool headerSkipped = false;
        std::string data, value;
        btc.uploadfile();
        
        while(std::getline(input, line))
        {
            if (line.empty()) continue;
            if(!headerSkipped && !isdigit(line[0]))
            {
                headerSkipped = true;
                continue ;
            }
            
            std::stringstream ss(line);
            if (!std::getline(ss, data, '|') || !std::getline(ss, value))
            {
	            std::cerr << "Error: bad input => " << line << std::endl;
	            continue ;
            }
            btc.printBtc(data, value);
        }
        input.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
   
    return (0);
}




