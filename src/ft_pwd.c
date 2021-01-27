/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:37:54 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/27 10:43:38 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int *fd)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, -1);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	buf = NULL;
	g_exit_ret = 0;
	if (fd)
	{
		close(fd[0]);
		write(fd[1], &g_exit_ret, sizeof(int));
		close(fd[1]);
	}
	exit(0);
}
