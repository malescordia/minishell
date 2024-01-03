NAME = minishell
FLAGS = -Wall -Wextra -Werror
RL_FLAGS = -lreadline -lhistory

SRC = src/main.c src/functions.c src/env.c src/echo.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) $(RL_FLAGS) -o $(NAME)
	@echo "\033[32m[success]\033[0m Minishell compiled!"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@
	@echo "\033[36m[compiled]\033[0m $<"

clean:
	@rm -f $(OBJ)
	@echo "\033[33m[clean]\033[0m Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m[fclean]\033[0m Executable file removed!"

re: fclean all