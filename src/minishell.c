/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:53:33 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/17 10:47:58 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_notfound(t_com *comm)
{
		write(1, "minishell: ", 12);
		write(1, comm->words[0], ft_strlen(comm->words[0]));
		write(1, ": command not found\n", 20);
		exit_ret = 127;
}

void	ft_bin_path(t_com *comm, char **env, char **tmp)
{
	pid_t	pod;
	int	res;
	int i;
	int status;

	i = 0;
	res = 0;
	clean_mem(comm->number_bin_path, NULL, comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);
	if (!ft_strchr(comm->words[0], '/'))
		tmp[0] = ft_strjoin(comm->bin_path[i], comm->words[0]);
	if (!(pod = fork()))
	{
		dup2(global_fd, 1);
		while ((res = execve(tmp[0], tmp, env) == -1) && comm->number_bin_path > i)
		{
			i++;
			if (!ft_strchr(comm->words[0], '/'))
				tmp[0] = ft_strjoin(comm->bin_path[i], comm->words[0]);
			if (i == comm->number_bin_path - 1)	
				ft_notfound(comm);
		}
		exit(exit_ret);
	}
	wait(&status);
	exit_ret = WEXITSTATUS(status);
}

void 	*ft_kill(pid_t pod)
{	
	kill(pod, 130);
	return (NULL);
}

void	ft_exec_path(t_com *comm, char **tmp_words, char **tmp_env)
{
	pid_t	pod;
	int status;
	int res = 0;
	
	if (!(pod = fork()))
	{
		signal (SIGINT, ft_kill(pod));
		dup2(global_fd, 1);
		res = execve(tmp_words[0], tmp_words, tmp_env);
		if (res == -1)
			ft_notfound(comm);
		exit(exit_ret);
	}
	wait(&status);
	if (exit_ret != 127)
		exit_ret = WEXITSTATUS(status);
	if (status == 2)
		exit_ret = 130;
}

void	ft_path(t_com * comm)
{
		char	**tmp_words;
		char	**tmp_env;
		int		j;

		j = 0;
		tmp_words = (char **)malloc(sizeof(char *) * (comm->number_words + 1));
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
		
		if (!ft_strncmp(tmp_words[0], "./", 2))
			ft_exec_path(comm, tmp_words, tmp_env);
		else
			ft_bin_path(comm, tmp_env, tmp_words);
		clean_mem((comm->number_words), NULL, tmp_words);
		clean_mem(ft_doublestrlen(comm->path), NULL, tmp_env);
		write(1, "\n", 1);
}

int		compare(t_com *comm)
{
	if (!ft_strcmp(comm->words[0], "exit"))
	{	
		exit_ret = 1;
		return (ft_exit(comm));
	}/*
	else if (!ft_strcmp(comm->words[0], "echo"))
		ft_echo(comm);
	else if (!ft_strcmp(comm->words[0], "cd"))
		ft_cd(comm);
	else if (!ft_strcmp(comm->words[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(comm->words[0], "env"))
		ft_env(comm);
	else if (!ft_strcmp(comm->words[0], "export"))
		ft_export(comm);
	else if (!ft_strcmp(comm->words[0], "unset"))
		ft_unset(comm);
	else
		ft_path(comm);*/
	return (-2);
}