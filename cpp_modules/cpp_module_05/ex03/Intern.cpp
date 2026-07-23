#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern(void)
{
}

Intern::Intern(const Intern &src)
{
	(void)src;
}

Intern::~Intern(void)
{
}

Intern	&Intern::operator=(const Intern &rhs)
{
	(void)rhs;
	return (*this);
}

AForm	*Intern::_createShrubbery(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

AForm	*Intern::_createRobotomy(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

AForm	*Intern::_createPresidential(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}

AForm	*Intern::makeForm(const std::string &formName, const std::string &target)
{
	const std::string	names[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm	*(*creators[])(const std::string &) = {
		&_createShrubbery,
		&_createRobotomy,
		&_createPresidential
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == names[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (creators[i](target));
		}
	}
	std::cout << "Intern cannot create form \"" << formName << "\": unknown form name." << std::endl;
	return (NULL);
}
