#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN &src)
	: _stack(src._stack)
{
}

RPN::~RPN(void)
{
}

RPN &RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
		this->_stack = rhs._stack;
	return (*this);
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void RPN::applyOperator(char op)
{
	int right;
	int left;
	int result;

	if (this->_stack.size() < 2)
		throw std::runtime_error("Error");

	right = this->_stack.top();
	this->_stack.pop();

	left = this->_stack.top();
	this->_stack.pop();

	if (op == '+')
		result = left + right;
	else if (op == '-')
		result = left - right;
	else if (op == '*')
		result = left * right;
	else
	{
		if (right == 0)
			throw std::runtime_error("Error");
		result = left / right;
	}

	this->_stack.push(result);
}

void RPN::calculate(const std::string &expression)
{
	std::size_t i;
	char c;

	i = 0;
	while (i < expression.length())
	{
		c = expression[i];

		if (c == ' ')
		{
			++i;
			continue;
		}

		if (c >= '0' && c <= '9')
		{
			this->_stack.push(c - '0');
		}
		else if (isOperator(c))
		{
			applyOperator(c);
		}
		else
		{
			throw std::runtime_error("Error");
		}

		++i;
	}

	if (this->_stack.size() != 1)
		throw std::runtime_error("Error");

	std::cout << this->_stack.top() << std::endl;
}