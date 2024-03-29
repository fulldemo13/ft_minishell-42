/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:53:33 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/07 10:25:41 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nosuchfile(char *word)
{
	write(1, "minishell: ", 12);
	write(1, word, ft_strlen(word));
	write(1, ": No such file or directory\n", 28);
	g_exit_ret = 1;
}

void	ft_notfound(char *word, int *fd)
{
	write(1, "minishell: ", 12);
	write(1, word, ft_strlen(word));
	write(1, ": command not found\n", 20);
	g_exit_ret = 127;
	if (fd)
	{
		close(fd[0]);
		write(fd[1], &g_exit_ret, sizeof(int));
		close(fd[1]);
	}
}

void	ft_bin_path(t_com *comm, int i, int j)
{
	while (i < ft_doublestrlen(comm->words))
	{
		if (!ft_strcmp(comm->words[i], "|"))
		{
			ft_exec_pipe(comm, i, j);
			return ;
		}
		if (!ft_strcmp(comm->words[i], ">") || !ft_strcmp(comm->words[i], ">>"))
		{
			ft_write_fd(comm, i, j);
			return ;
		}
		if (!ft_strcmp(comm->words[i], "<"))
		{
			ft_read_fd(comm, i, j);
			return ;
		}
		i++;
	}
	if (i == ft_doublestrlen(comm->words))
		ft_exec_stdout(comm, i, j);
}

void	ft_searchexec(t_com *comm, char **tmp, int *fd)
{
	if (!ft_strcmp(tmp[0], "echo") && comm->bin_path)
		ft_echo(tmp, fd);
	else if (!ft_strcmp(tmp[0], "pwd") && comm->bin_path)
		ft_pwd(fd);
	else if (!ft_strcmp(tmp[0], "env") && comm->bin_path)
		ft_env(comm, tmp, fd);
	else if (!ft_strcmp(tmp[0], "export") && comm->bin_path)
		ft_export_child(comm, tmp, fd);
	else
		ft_exec_comm(comm, tmp, fd);
}

int		compare(t_com *comm)
{
	if (!ft_strcmp(comm->words[0], "exit"))
		return (ft_exit(comm));
	else if (!ft_strcmp(comm->words[0], "cd") && comm->bin_path)
		ft_cd(comm);
	else if (!ft_strcmp(comm->words[0], "unset") && comm->bin_path)
		ft_unset(comm);
	else
		ft_bin_path(comm, 0, 0);
	return (-1);
}
