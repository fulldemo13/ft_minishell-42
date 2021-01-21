/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:22:03 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/21 15:49:23 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_com *comm, char **tmp, int *fd)
{
	if (ft_doublestrlen(tmp) > 1)
	{
		write(1, "env: ", 5);
		write(1, tmp[1], ft_strlen(tmp[1]));
		write(1, ": No such file or directory\n", 28);
		exit_ret = 127;
	}
	else
	{
		ft_putstr(comm->path);
		exit_ret = 0;
	}
	if (fd)
	{
		close(fd[0]);
		write(fd[1], &exit_ret, sizeof(int));
		close(fd[1]);
	}
	exit(0);
}