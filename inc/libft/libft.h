/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:09:17 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 19:19:26 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define PURPLE "\033[35m"
# define BLUE "\033[36m"
# define R "\033[0m"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstnew(void *content);

size_t					ft_strlen(const char *str);
size_t					ft_strlcat(char *dst, const char *src, size_t len);

unsigned int			ft_strlcpy(char *dest, const char *src, size_t size);

void					ft_printlist(t_list *lst);
void					ft_putnbr_fd(int n, int fd);
void					ft_putchar_fd(char c, int fd);
void					ft_bzero(void *str, size_t n);
void					ft_putstr_fd(char *str, int fd);
void					*ft_calloc(size_t n, size_t len);
void					ft_putendl_fd(char *str, int fd);
void					*ft_memset(void *str, int c, size_t n);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));

int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_islower(int c);
int						ft_isupper(int c);
int						ft_lstsize(t_list *lst);
int						ft_atoi(const char *str);
unsigned long long int	ft_atoulli(const char *str);
int						ft_strcmp(char *s1, char *s2);
int						ft_strlen_chr(char *str, char c);
int						ft_strcmp_chr(char *s1, char *s2, char c);
int						ft_strcmp_nochr(char *s1, char *s2, char c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

char					*ft_itoa(int n);
char					*ft_strdup(const char *str);
char					*ft_strndup(char *str, int len);
char					*ft_strchr(const char *str, int c);
char					**ft_split(const char *str, char c);
char					*ft_strrchr(const char *str, int c);
char					*ft_strfront_trim(char *str, char *trim);
char					*ft_strjoin(const char *s1, const char *s2);
char					*ft_strtrim(const char *str, const char *trim);
char					*ft_substr(const char *str, unsigned int start, 
							size_t len);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);

#endif
