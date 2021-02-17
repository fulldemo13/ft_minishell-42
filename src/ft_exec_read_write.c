/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_read_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:29:16 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/15 10:01:19 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((fd = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777))
		== -1)
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
