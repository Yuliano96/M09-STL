/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:52:51 by yuliano           #+#    #+#             */
/*   Updated: 2026/04/29 21:26:43 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <exception>
#include <iostream>

class RPN
{
	private:

	std::string input;
	std::stack<int> stack;

	public:
	
	RPN();
	RPN(const std::string &_input);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	bool isNumValid(const char token);
	bool isOperator(const char token);
	int calculExpression(int a, int b, const char op);
	int add(int a, int b);
	int subtract(int a, int b);
	int multiply(int a, int b);
	int divide(int a, int b);
	int RPN_calculation();
};

#endif