#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include "AForm.hpp"

class Intern
{
public:
	Intern(void);
	Intern(const Intern &src);
	~Intern(void);

	Intern	&operator=(const Intern &rhs);

	AForm	*makeForm(const std::string &formName, const std::string &target);

private:
	static AForm	*_createShrubbery(const std::string &target);
	static AForm	*_createRobotomy(const std::string &target);
	static AForm	*_createPresidential(const std::string &target);
};

#endif
