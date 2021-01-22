/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:53:33 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/22 11:46:14 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nosuchfile(char *word)
{
		write(1, "minishell: ", 12);
		write(1, word, ft_strlen(word));
		write(1, ": No such file or directory\n", 28);
		exit_ret = 1;
}

void	ft_notfound(char *word, int *fd)
{
		write(1, "minishell: ", 12);
		write(1, word, ft_strlen(word));
		write(1, ": command not found\n", 20);
		exit_ret = 127;
		close(fd[0]);
		write(fd[1], &exit_ret, sizeof(int));
		close(fd[1]);
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