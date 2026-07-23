#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN &src)
{
	(void)src;
}

RPN::~RPN(void)
{
}

RPN &RPN::operator=(const RPN &rhs)
{
	(void)rhs;
	return (*this);
}

bool RPN::isOperator(const std::string &token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::performOperation(int a, int b, const std::string &op)
{
	if (op == "+")
		return (a + b);
	else if (op == "-")
		return (a - b);
	else if (op == "*")
		return (a * b);
	else if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Division by zero");
		return (a / b);
	}
	return (0);
}

int RPN::evaluate(const std::string &expression)
{
	std::stack<int> stack;
	std::string token;
	std::istringstream iss(expression);

	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error");

			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();

			stack.push(performOperation(a, b, token));
		}
		else
		{
			if (token.length() > 1)
				throw std::runtime_error("Error");

			if (!std::isdigit(token[0]))
				throw std::runtime_error("Error");

			stack.push(std::atoi(token.c_str()));
		}
	}

	if (stack.size() != 1)
		throw std::runtime_error("Error");

	return (stack.top());
}