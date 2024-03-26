NAME = libft.a

SRC =  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c \
		ft_lstnew.c ft_lstsize.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strlen_chr.c ft_strcmp_chr.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c ft_lstclear.c ft_lstdelone.c \
		ft_islower.c ft_isupper.c ft_strcmp_nochr.c ft_strfront_trim.c ft_strndup.c ft_strtrim.c ft_atoulli.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -crs $(NAME) $(OBJ) 
	@echo "\033[32m[success]\033[0m Libft compiled!"

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[33m[clean]\033[0m Libft object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m[fclean]\033[0m Libft.a file removed!"

re: fclean all