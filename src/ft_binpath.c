/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:43:39 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 12:50:48 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	wc < hola.txt
*/

void	ft_end_fd(t_com *comm, char **tmp, int fd)
{
	if (comm->pipe != -1)
		ft_close_pipes(comm->fd[comm->pipe]);
	comm->pipe = -1;
	close(fd);
	ft_clean_mem(tmp);
}

void	ft_read_fd(t_com *comm, int i, int j)
{
	char	**tmp;
	pid_t	pod;
	int		status;
	int		fd;

	if ((fd = open(comm->words[i + 1], O_RDONLY)) == -1)
	{
		ft_nosuchfile(comm->words[i + 1]);
		return ;
	}
	tmp = ft_relode_binpath_getexe(comm, i, j);
	if (comm->pipe >= 1)
		ft_close_pipes(comm->fd[comm->pipe - 1]);
	if (!(pod = fork()))
	{	
		dup2(fd, STDIN_FILENO);
		if (comm->pipe != -1)
			ft_exec_dup2(comm->fd[comm->pipe], 1, STDOUT_FILENO);
		ft_searchexec(comm, tmp, NULL);
	}
	wait(&status);
	ft_end_fd(comm, tmp, fd);
}

/*
**	env > hola.txt
**	j es la posición siguiente a la última redireccíon
**	i es la posicion de la redirección actual
*/

int		ft_open_files_write(char **words, int fd, int i)
{
	if (!ft_strcmp(words[i], ">"))
	{
		if (fd != -1)
			close(fd);
		if ((fd = open(words[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
		{
			ft_notfound(words[i + 1], NULL);
			return (-1);
		}
	}
	if (!ft_strcmp(words[i], ">>"))
	{
		if (fd != -1)
			close(fd);
		if ((fd = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0777)) == -1)
		{
			ft_notfound(words[i + 1], NULL);
			return (-1);
		}
	}
	return (fd);
}

void	ft_write_fd(t_com *comm, int i, int j)
{
	char	**tmp;
	pid_t	pod;
	int		status;
	int		fd;
	
	fd = -1;
	tmp = ft_relode_binpath_getexe(comm, i, j);
	while (comm->words[i + 1] != NULL)
	{	
		fd = ft_open_files_write(comm->words, fd, i);
		i++;
	}
	comm->pipe >= 1 ? ft_close_pipes(comm->fd[comm->pipe - 1]) : 0;
	if (!(pod = fork()))
	{
		dup2(fd, STDOUT_FILENO);
		if (comm->pipe != -1)
			ft_exec_dup2(comm->fd[comm->pipe], 0, STDIN_FILENO);
		ft_searchexec(comm, tmp, NULL);
	}
	wait(&status);
	ft_end_fd(comm, tmp, fd);
}

/*
**	Escribe en STDOUT
*/

void	ft_exit_ret_stdout(t_com *comm, int i, int j, int *efd)
{
	exit_ret = 0;	
	if (!(i && (j == 0)))
		exit_ret = 1;	
	if (comm->pipe == -1)
	{
		close(efd[1]);
		read(efd[0], &exit_ret, sizeof(int));
		close(efd[0]);
	}
}

void ft_exec_stdout(t_com *comm, int i, int j)
{
	char	**tmp;
	pid_t	pod;
	int		status;
	int		efd[2];
	
	tmp = ft_relode_binpath_getexe(comm, i, j);
	comm->pipe >= 1 ? ft_close_pipes(comm->fd[comm->pipe - 1]) : 0;
	comm->pipe == -1 ? pipe(efd) : 0;
	if (!(pod = fork()))
	{
		if (comm->pipe != -1)
			ft_exec_dup2(comm->fd[comm->pipe], 0, STDIN_FILENO);
		ft_searchexec(comm, tmp, efd);
	}
	wait(&status);
	ft_exit_ret_stdout(comm, WIFEXITED(status), WEXITSTATUS(status), efd);
	!ft_strcmp(tmp[0], "export") ? ft_export_parent(comm, tmp) : 0;
	comm->pipe != -1 ? ft_close_pipes(comm->fd[comm->pipe]) : 0;
	comm->pipe = -1;
	ft_clean_mem(tmp);
}

/*
**	PIPES ||||
*/

void	ft_exec_pipe(t_com *comm, int i, int j)
{
	char **tmp;
	pid_t pod;
	int status;

	tmp = ft_relode_binpath_getexe(comm, i, j);
	comm->pipe++;
	pipe(comm->fd[comm->pipe]);
	comm->pipe >= 2 ? ft_close_pipes(comm->fd[comm->pipe - 2]) : 0;
	if (!(pod = fork()))
	{
		if (comm->pipe == 0)
			ft_exec_dup2(comm->fd[comm->pipe], 1, STDOUT_FILENO);
		else
		{
			ft_exec_dup2(comm->fd[comm->pipe - 1], 0, STDIN_FILENO);
			ft_exec_dup2(comm->fd[comm->pipe], 1, STDOUT_FILENO);
		}
		ft_searchexec(comm, tmp, NULL);
	}		
	ft_clean_mem(tmp);
	ft_bin_path(comm, i + 1, i + 1);
	wait(&status);
}