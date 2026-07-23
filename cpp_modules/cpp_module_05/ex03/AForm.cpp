#include "AForm.hpp"

AForm::AForm(void) : _name("default"), _signed(false), _signGrade(150), _execGrade(150)
{
}

AForm::AForm(const std::string &name, int signGrade, int execGrade) :
	_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw AForm::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &src) :
	_name(src._name), _signed(src._signed), _signGrade(src._signGrade), _execGrade(src._execGrade)
{
}

AForm::~AForm(void)
{
}

AForm	&AForm::operator=(const AForm &rhs)
{
	if (this != &rhs)
		this->_signed = rhs._signed;
	return (*this);
}

const std::string	&AForm::getName(void) const
{
	return (this->_name);
}

bool	AForm::getSigned(void) const
{
	return (this->_signed);
}

int	AForm::getSignGrade(void) const
{
	return (this->_signGrade);
}

int	AForm::getExecGrade(void) const
{
	return (this->_execGrade);
}

void	AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_signGrade)
		throw AForm::GradeTooLowException();
	this->_signed = true;
}

void	AForm::execute(const Bureaucrat &executor) const
{
	if (!this->_signed)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->_execGrade)
		throw AForm::GradeTooLowException();
	this->action();
}

const char	*AForm::GradeTooHighException::what(void) const throw()
{
	return ("grade too high");
}

const char	*AForm::GradeTooLowException::what(void) const throw()
{
	return ("grade too low");
}

const char	*AForm::FormNotSignedException::what(void) const throw()
{
	return ("form not signed");
}

std::ostream	&operator<<(std::ostream &o, const AForm &rhs)
{
	o << "Form " << rhs.getName()
	  << ", signed: " << (rhs.getSigned() ? "yes" : "no")
	  << ", sign grade: " << rhs.getSignGrade()
	  << ", exec grade: " << rhs.getExecGrade() << ".";
	return (o);
}
