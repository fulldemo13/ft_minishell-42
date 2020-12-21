/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:53:33 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/21 09:51:42 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_notfound(char *word)
{
		write(1, "minishell: ", 12);
		write(1, word, ft_strlen(word));
		write(1, ": error\n", 8);
		//exit_ret = 127;
}

void 	*ft_kill(pid_t pod)
{	
	kill(pod, 130);
	return (NULL);
}

void	ft_exec_path(t_com *comm)
{
	pid_t	pod;
	int status;
	int res = 0;
	
	if (!(pod = fork()))
	{
		signal (SIGINT, ft_kill(pod));
	//	dup2(global_fd, 1);
		res = execve(comm->words[0], comm->words, comm->path);
		if (res == -1)
			ft_notfound(comm->words[0]);
	//	exit(exit_ret);
	}
	wait(&status);
/*	if (exit_ret != 127)
		exit_ret = WEXITSTATUS(status);
	if (status == 2)
		exit_ret = 130;*/
}

int		compare(t_com *comm)
{
	if (!ft_strcmp(comm->words[0], "exit"))
		return (ft_exit(comm));
	else if (!ft_strcmp(comm->words[0], "cd"))
		ft_cd(comm);
	else if (!ft_strcmp(comm->words[0], "unset"))
		ft_unset(comm);
	else
		ft_bin_path(comm, 0, 0);
	return (-2);
}