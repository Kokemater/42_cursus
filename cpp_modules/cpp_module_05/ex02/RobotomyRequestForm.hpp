#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &src);
	~RobotomyRequestForm(void);

	RobotomyRequestForm	&operator=(const RobotomyRequestForm &rhs);

	const std::string	&getTarget(void) const;

private:
	std::string	_target;

	void	action(void) const;
};

#endif
