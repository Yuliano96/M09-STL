/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:37:48 by yuliano           #+#    #+#             */
/*   Updated: 2026/04/29 21:25:40 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN():input("") {}
RPN::RPN(const std::string &_input):input(_input) {}
RPN::RPN(const RPN &other):input(other.input),stack(other.stack) {}
RPN &RPN::operator=(const RPN &other)
{
	if(this != & other)
	{
		this->input = other.input;
		this->stack = other.stack;
	}
	return *this;
}

RPN::~RPN() {}

bool RPN::isNumValid(const char token)
{
	if (token >= '0' && token <= '9')
		return true;
	return false;
}

bool RPN::isOperator(const char token)
{
	const char op [] = {'+', '-', '/', '*'};
	for(int i = 0; i < 4; i++)
	{
		if (token == op[i])
			return true;
	}
	return false;
}

int RPN::add(int a, int b)
{
	return (a + b);
}

int RPN::subtract(int a, int b)
{
	return (a - b);
}

int RPN::divide(int a, int b)
{
	if (b == 0)
		throw std::runtime_error("Error: invalid division");
	return (a / b);
}

int RPN::multiply(int a, int b)
{
	return (a * b);
}

int RPN::calculExpression(int a, int b, const char token)
{
	const char op [] = {'+', '-', '/', '*'};
	
	int (RPN::*expression[])(int a, int b) = 
	{
		&RPN::add,
		&RPN::subtract,
		&RPN::divide,
		&RPN::multiply,
	};

	for (int i = 0; i < 4; i++)
	{
		if (token == op[i])
		{
			return ((this ->*expression[i])(a, b));
		}
	}
	return (-1);
}

int RPN::RPN_calculation()
{
	int a, b;

	for(size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') continue;
		if(isNumValid(input[i]))
		{
			stack.push(input[i] - '0');
			if (i + 1 < input.size() && input[i + 1] != ' ')
				throw std::invalid_argument("Error: Invalid format");
		}
		else if(isOperator(input[i]))
		{
			if(stack.size() < 2) 
                throw std::runtime_error("Error: Operands are missing");
			b = stack.top(); stack.pop();
			a = stack.top(); stack.pop();
			stack.push(calculExpression(a, b, input[i]));
			if (i + 1 < input.size() && input[i + 1] != ' ')
				throw std::invalid_argument("Error: Invalid format");
		}
		else
			throw std::invalid_argument("Error: Invalid argument");
	}
	if(stack.size() > 1 || stack.empty())
		throw std::runtime_error("Error: incorrect operation");
	return (stack.top());
}
