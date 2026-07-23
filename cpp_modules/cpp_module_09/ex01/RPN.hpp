#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>
# include <cstdlib>

class RPN
{
public:
	RPN(void);
	RPN(const RPN &src);
	~RPN(void);

	RPN &operator=(const RPN &rhs);

	static int evaluate(const std::string &expression);

private:
	static bool isOperator(const std::string &token);
	static int performOperation(int a, int b, const std::string &op);
};

#endif