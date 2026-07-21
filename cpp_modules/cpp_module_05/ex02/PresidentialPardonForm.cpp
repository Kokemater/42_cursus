#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) :
	AForm("Presidential Pardon", 25, 5), _target("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) :
	AForm("Presidential Pardon", 25, 5), _target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src) :
	AForm(src), _target(src._target)
{
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &rhs)
{
	if (this != &rhs)
	{
		AForm::operator=(rhs);
		this->_target = rhs._target;
	}
	return (*this);
}

const std::string	&PresidentialPardonForm::getTarget(void) const
{
	return (this->_target);
}

void	PresidentialPardonForm::action(void) const
{
	std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
