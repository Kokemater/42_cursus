#include "Form.hpp"

Form::Form(void) : _name("default"), _signed(false), _signGrade(150), _execGrade(150)
{
}

Form::Form(const std::string &name, int signGrade, int execGrade) :
	_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw Form::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form &src) :
	_name(src._name), _signed(src._signed), _signGrade(src._signGrade), _execGrade(src._execGrade)
{
}

Form::~Form(void)
{
}

Form	&Form::operator=(const Form &rhs)
{
	if (this != &rhs)
		this->_signed = rhs._signed;
	return (*this);
}

const std::string	&Form::getName(void) const
{
	return (this->_name);
}

bool	Form::getSigned(void) const
{
	return (this->_signed);
}

int	Form::getSignGrade(void) const
{
	return (this->_signGrade);
}

int	Form::getExecGrade(void) const
{
	return (this->_execGrade);
}

void	Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_signGrade)
		throw Form::GradeTooLowException();
	this->_signed = true;
}

const char	*Form::GradeTooHighException::what(void) const throw()
{
	return ("grade too high");
}

const char	*Form::GradeTooLowException::what(void) const throw()
{
	return ("grade too low");
}

std::ostream	&operator<<(std::ostream &o, const Form &rhs)
{
	o << "Form " << rhs.getName()
	  << ", signed: " << (rhs.getSigned() ? "yes" : "no")
	  << ", sign grade: " << rhs.getSignGrade()
	  << ", exec grade: " << rhs.getExecGrade() << ".";
	return (o);
}
