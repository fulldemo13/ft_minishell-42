/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:22:54 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/13 11:12:52 by fulldemo         ###   ########.fr       */
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

int		exit_ret;
int		global_fd;
pid_t		g_pid;

typedef struct	s_com
{
	int		number_com;
	int		number_words;
	int		number_path;
	int		number_bin_path;
	char	**commands;
	char	**words;
	char	**path;
	char	**bin_path;
}				t_com;

int		get_next_line(char **line);
int		is_space(char c);
int		divider(char *line);
void	fill_commands(char *line, char **commands);
char	**get_commands(char *line);
void	clean_mem(int words, char *line, char **commands);
void	ft_putstr(char **str, int len);
int		ft_semicolon(char *line);
int		compare(t_com *comm);
char	*ft_strnjoin(char *s1, char *s2, size_t len);
char	*ft_strndup(const char *s1, size_t len);
char	**ft_removestr(char **path, int pos, int len);

void	ft_echo(t_com *comm);
void	ft_cd(t_com *comm);
void	ft_pwd(void);
void	ft_env(t_com *comm);
void	ft_export(t_com *comm);
void	ft_unset(t_com *comm);
int		ft_exit(t_com *comm);
int		ft_doublestrlen(char **s);
char	**ft_doublestrdup(char **str, int i);
char	**ft_addstr(char **path, int number_path, char *str);
int		ft_searchpath(t_com *comm, char *words);
t_com	*ft_comm_initialize(int argc, char **argv, char **env, t_com *comm);
char	**parse_redirection(t_com *comm);
void	get_fd(t_com *comm);
char	**ft_getbinpath(t_com *comm);

int		is_redirection(char c);
int		ft_quotes(char *line);
void	check_quotes(t_com *comm);
int		ft_check_syntax(char *line);

#endif