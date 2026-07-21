#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <string>
# include "Bureaucrat.hpp"

class AForm
{
public:
	AForm(void);
	AForm(const std::string &name, int signGrade, int execGrade);
	AForm(const AForm &src);
	virtual ~AForm(void);

	AForm	&operator=(const AForm &rhs);

	const std::string	&getName(void) const;
	bool				getSigned(void) const;
	int					getSignGrade(void) const;
	int					getExecGrade(void) const;

	void	beSigned(const Bureaucrat &bureaucrat);
	void	execute(const Bureaucrat &executor) const;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual const char	*what() const throw();
	};

private:
	const std::string	_name;
	bool				_signed;
	const int			_signGrade;
	const int			_execGrade;

	virtual void	action(void) const = 0;
};

std::ostream	&operator<<(std::ostream &o, const AForm &rhs);

#endif
