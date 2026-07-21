#include "RobotomyRequestForm.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(void) :
	AForm("Robotomy Request", 72, 45), _target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) :
	AForm("Robotomy Request", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src) :
	AForm(src), _target(src._target)
{
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	if (this != &rhs)
	{
		AForm::operator=(rhs);
		this->_target = rhs._target;
	}
	return (*this);
}

const std::string	&RobotomyRequestForm::getTarget(void) const
{
	return (this->_target);
}

void	RobotomyRequestForm::action(void) const
{
	std::cout << "* DRILLING NOISES * BZZZZZT" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << this->_target << " has been robotomized successfully." << std::endl;
	else
		std::cout << "Robotomy of " << this->_target << " failed." << std::endl;
}
