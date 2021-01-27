/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_stdout_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:43:39 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/27 10:44:03 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_ret_stdout(t_com *comm, int i, int j, int *efd)
{
	g_exit_ret = 0;
	if (!(i && (j == 0)))
		g_exit_ret = 1;
	if (comm->pipe == -1)
	{
		close(efd[1]);
		read(efd[0], &g_exit_ret, sizeof(int));
		close(efd[0]);
	}
}

void	ft_exec_stdout(t_com *comm, int i, int j)
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

void	ft_exec_pipe(t_com *comm, int i, int j)
{
	char	**tmp;
	pid_t	pod;
	int		status;

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
