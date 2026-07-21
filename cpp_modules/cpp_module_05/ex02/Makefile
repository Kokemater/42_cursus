SRC = Bureaucrat.cpp \
      AForm.cpp \
      ShrubberyCreationForm.cpp \
      RobotomyRequestForm.cpp \
      PresidentialPardonForm.cpp \
      main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = bureaucrat

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(CPPFLAGS) $(OBJ) -o $@

%.o: %.cpp
	c++ $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
