/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:22:54 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/27 10:41:01 by fulldemo         ###   ########.fr       */
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

typedef struct	s_quo
{
	int			i;
	int			j;
	int			len;
	char		*tmp;
	char		*aux;
}				t_quo;

typedef struct	s_div
{
	int			i;
	int			total;
	int			flag;
	int			f_simple;
	int			f_double;
	int			f_redirection;
}				t_div;

typedef struct	s_com
{
	char		**commands;
	char		**words;
	char		**path;
	char		**bin_path;
	int			fd[MAX_LEN][2];
	int			pipe;
}				t_com;

int				g_exit_ret;

int				ft_divisor(char *line);
int				ft_malloc_words(char *line, char **words);
int				ft_fill_words(char *line, char **words);
void			ft_bin_path(t_com *comm, int i, int j);
void			ft_div_init(t_div *div);
void			ft_divisor_quotes(char *line, t_div *div);
void			ft_nosuchfile(char *word);
void			ft_notfound(char *word, int *fd);
void			ft_echo(char **tmp, int *fd);
void			ft_cd(t_com *comm);
void			ft_pwd(int *fd);
void			ft_env(t_com *comm, char **tmp, int *fd);
void			ft_export_parent(t_com *comm, char **tmp);
void			ft_export_child(t_com *comm, char **tmp, int *fd);
int				ft_addstr(t_com *comm, char *new);
void			ft_unset(t_com *comm);
int				ft_exit(t_com *comm);
int				ft_sig_exit();
int				ft_doublestrlen(char **s);
char			**ft_doublestrdup(char **str);
int				get_next_line(char **line);
void			ft_clean_mem(char **commands);
void			ft_putstr(char **str);
int				compare(t_com *comm);
char			*ft_strnjoin(char *s1, char *s2, size_t len);
char			*ft_strndup(const char *s1, size_t len);
void			ft_read_fd(t_com *comm, int i, int j);
void			ft_write_fd(t_com *comm, int i, int j);
void			ft_exec_stdout(t_com *comm, int i, int j);
void			ft_exec_pipe(t_com *comm, int i, int j);
void			ft_exec_comm(t_com *comm, char **tmp, int *fd);
char			**ft_to_execute(t_com *comm, int i, int j);
void			ft_searchexec(t_com *comm, char **tmp, int *fd);
void			ft_close_pipes(int *fd);
void			ft_exec_dup2(int *fd, int i, int j);
char			**ft_relode_binpath_getexe(t_com *comm, int i, int j);
int				ft_searchpath(t_com *comm, char *words);
char			**ft_getbinpath(t_com *comm);
int				is_redirection(char c);
void			ft_check_quotes_dolar(t_com *comm);
char			*check_dollar(t_com *comm, int i, int j, char *tmp);
char			*check_home(char *word, t_com *comm);
int				ft_redirections(char *line);
int				ft_check_syntax(char *line);

#endif
