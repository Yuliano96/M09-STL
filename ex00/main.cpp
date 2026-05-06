/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:44:24 by yuliano           #+#    #+#             */
/*   Updated: 2026/05/06 21:21:15 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"



int main()
{
    std::map<std::string, std::string>::iterator it;
    BitcoinExchange bit;
    bit.uploadfile();
    it = bit.searchDate("2006-01-04");
    std::cout<<it->first << " | "<<it->second<<std::endl;
    return (0);
}




