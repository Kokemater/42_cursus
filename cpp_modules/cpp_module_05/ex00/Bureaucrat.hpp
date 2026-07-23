#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <stdexcept>

class Bureaucrat
{
public:
	Bureaucrat(void);
	Bureaucrat(const std::string &name, int grade);
	Bureaucrat(const Bureaucrat &src);
	~Bureaucrat(void);

	Bureaucrat	&operator=(const Bureaucrat &rhs);

	const std::string	&getName(void) const;
	int					getGrade(void) const;

	void	increment(void);
	void	decrement(void);

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
	int					_grade;
};

std::ostream	&operator<<(std::ostream &o, const Bureaucrat &rhs);

#endif
