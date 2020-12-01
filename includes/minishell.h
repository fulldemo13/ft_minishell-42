/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:22:54 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 10:15:32 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"

# define MAX_LEN 4096
/*
int		exit_ret;
int		global_fd;
pid_t		g_pid;
*/
typedef struct	s_com
{
//	int		number_com;
//	int		number_words;
//	int		number_path;
	int		number_bin_path;
	char	**commands;
	char	**words;
	char	**path;
	char	**bin_path;
	int 	fd[MAX_LEN][2];
	int		pipe;
}				t_com;




int ft_divisor(char *line);
int ft_malloc_words(char *line, char **words);
int ft_fill_words(char *line, char **words);
void ft_bin_path(t_com *comm, int i, int j);
void ft_notfound(char *word);

void	ft_echo(char **tmp);
void	ft_cd(t_com *comm);
void	ft_pwd(void);
void	ft_env(t_com *comm, char **tmp);
void	ft_export_parent(t_com *comm, char **tmp);
void	ft_export_child(t_com *comm, char **tmp);
void	ft_unset(t_com *comm);
int		ft_exit(t_com *comm);

int		ft_doublestrlen(char **s);
char	**ft_doublestrdup(char **str);
char	**ft_addstr(char **str, char *new);


void	ft_showdouble(char **str);

int		get_next_line(char **line);
int		is_space(char c);
void	clean_mem(int words, char *line, char **commands);
void	clean_mem2(char **commands);
void	ft_putstr(char **str);
int		ft_semicolon(char *line);
int		compare(t_com *comm);
char	*ft_strnjoin(char *s1, char *s2, size_t len);
char	*ft_strndup(const char *s1, size_t len);
char	**ft_removestr(char **path, int pos, int len);




int		ft_searchpath(t_com *comm, char *words);
t_com	*ft_comm_initialize(int argc, char **argv, char **env, t_com *comm);
char	**ft_getbinpath(t_com *comm);

int		is_redirection(char c);
int		ft_quotes(char *line);
void	check_quotes(t_com *comm);
int		ft_check_syntax(char *line);

#endif