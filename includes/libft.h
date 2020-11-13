/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:16:48 by jmartine          #+#    #+#             */
/*   Updated: 2020/02/13 19:42:59 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <ctype.h>

void			*ft_memset(void *str, int c, size_t len);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
size_t			ft_strlen(const char *s);
void			ft_bzero(void *str, size_t n);
char			*ft_strdup(char *s1);
void			*ft_memmove(void *str1, const void *str2, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *dst, const void *str, size_t n);
int				ft_isalpha(int n);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(char *s1, char a);
char			*ft_strrchr(const char *str, int c);
int				ft_strncmp(const char *str, const char *str2, size_t c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(const char *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_strcpy(char *dst, const char *src);
int				ft_strcmp(const char *s1, const char *s2);

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(const void *content);
void			*ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));

#endif
