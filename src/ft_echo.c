/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:42:06 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/21 15:46:31 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(char **tmp, int *fd)
{
	int i;
	int	ret;

	ret = 0;
	i = 1;
	if (tmp[i] != NULL)
		if ((ret = ft_strcmp(tmp[i], "-n")) == 0)
			i++;
	while ((tmp[i] != NULL))
	{
		write(1, tmp[i], ft_strlen(tmp[i]));
		i++;
		if (ft_doublestrlen(tmp) > i)
				write(1, " ", 1);
	}
	if (ft_doublestrlen(tmp) == 1)
		write(1, "\n", 1);
	if (ret)
		write(1, "\n", 1);
		
	exit_ret = 0;
	if (fd)
	{
		close(fd[0]);
		write(fd[1], &exit_ret, sizeof(int));
		close(fd[1]);
	}
	exit(0);
}