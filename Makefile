NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC =   src/main.c src/check_input_1.c src/parse.c src/quote_utils.c \
		src/expansion.c src/expansion_utils.c src/init.c src/split.c \
		src/input_utils.c src/free_1.c src/tokenize.c src/cmd.c \
		src/redirection.c src/error_1.c src/start_protocol.c src/execute.c \
		src/builtins.c src/check_cmd.c src/utils_1.c \
		src/builtins/env.c src/builtins/cd.c src/builtins/echo.c \
		src/builtins/pwd.c src/builtins/exit.c src/builtins/unset.c \
		src/builtins/export.c src/signal_catch.c src/check_input_2.c \
		src/utils_2.c src/error_2.c src/heredoc.c src/heredoc_utils.c \
		src/free_2.c \

OBJ = $(SRC:.c=.o)

LIBFT = inc/libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC inc/libft
	@cc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\033[32m[success]\033[0m Minishell compiled!"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@
	@echo "\033[36m[compiled]\033[0m $<"

clean:
	@rm -f $(OBJ) inc/libft/*.o
	@echo "\033[33m[clean]\033[0m Object files removed!"

fclean: clean
	@make fclean -sC inc/libft/
	@rm -f $(NAME)
	@echo "\033[31m[fclean]\033[0m Executable file removed!"

re: fclean all

v:
	@make && valgrind --leak-check=full --show-leak-kinds=all --suppressions="readline.supp" ./minishell