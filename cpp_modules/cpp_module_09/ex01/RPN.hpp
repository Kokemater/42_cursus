#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>
# include <stdexcept>

class RPN
{
public:
	RPN(void);
	RPN(const RPN &src);
	~RPN(void);

	RPN &operator=(const RPN &rhs);

	void calculate(const std::string &expression);

private:
	std::stack<int> _stack;

	bool isOperator(char c) const;
	void applyOperator(char op);
};

#endif