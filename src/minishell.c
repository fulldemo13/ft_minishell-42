/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:53:33 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 10:55:17 by fulldemo         ###   ########.fr       */
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
/*
void	ft_bin_path(t_com *comm)
{
	pid_t	pod;
	int	res;
	int i;
	int status;
	char *tmp;

	i = 0;
	res = 0;
	clean_mem2(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);
//	if (!ft_strchr(comm->words[0], '/'))
//		comm->words[0] = ft_strjoin(comm->bin_path[i], comm->words[0]);
	if (!(pod = fork()))
	{
		dup2(global_fd, 1);
		tmp = ft_strjoin(comm->bin_path[i], comm->words[0]);
		while ((res = execve(tmp, comm->words, comm->path) == -1) || comm->bin_path[i] != NULL)
		{
			i++;
			free(tmp);
			tmp = ft_strjoin(comm->bin_path[i], comm->words[0]);
		}
		free(tmp);
		if ((res = execve(comm->words[0], comm->words, comm->path)) == -1)
			ft_notfound(comm);
		exit(exit_ret);
	}
	wait(&status);
	exit_ret = WEXITSTATUS(status);
}
*/
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

void	ft_path(t_com * comm)
{
	//	char	**tmp_words;
	//	char	**tmp_env;
		int		j;

		j = 0;
	/*	tmp_words = (char **)malloc(sizeof(char *) * (comm->number_words + 1));
		tmp_env = (char **)malloc(sizeof(char *) * (ft_doublestrlen(comm->path) + 1));
		while (comm->number_words > j)
		{
			tmp_words[j] = ft_strdup(comm->words[j]);
			j++;
		}
		tmp_words[j] = NULL;
		j  = 0;
		while (comm->path[j] != NULL)
		{
			tmp_env[j] = ft_strdup(comm->path[j]);
			j++;
		}
		tmp_env[j] = NULL;
		
		if (!ft_strncmp(comm->words[0], "./", 2))
			ft_exec_path(comm);
		else
	*/		ft_bin_path(comm, 0, 0);
	/*	clean_mem((comm->number_words), NULL, tmp_words);
		clean_mem(ft_doublestrlen(comm->path), NULL, comm->path);
		write(1, "\n", 1);*/
}

int		compare(t_com *comm)
{
	if (!ft_strcmp(comm->words[0], "exit"))
	{	
		//exit_ret = 1;
		return (ft_exit(comm));
	}
	else if (!ft_strcmp(comm->words[0], "cd"))
		ft_cd(comm);
	else if (!ft_strcmp(comm->words[0], "unset"))
		ft_unset(comm);
	else
		ft_path(comm);
	return (-2);
}