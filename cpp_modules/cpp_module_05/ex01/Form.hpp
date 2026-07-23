#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include "Bureaucrat.hpp"

class Form
{
public:
	Form(void);
	Form(const std::string &name, int signGrade, int execGrade);
	Form(const Form &src);
	~Form(void);

	Form	&operator=(const Form &rhs);

	const std::string	&getName(void) const;
	bool				getSigned(void) const;
	int					getSignGrade(void) const;
	int					getExecGrade(void) const;

	void	beSigned(const Bureaucrat &bureaucrat);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

private:
	const std::string	_name;
	bool				_signed;
	const int			_signGrade;
	const int			_execGrade;
};

std::ostream	&operator<<(std::ostream &o, const Form &rhs);

#endif
