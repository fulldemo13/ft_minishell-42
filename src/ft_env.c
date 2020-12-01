/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:22:03 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 09:20:21 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_com *comm, char **tmp)
{
	if (ft_doublestrlen(tmp) > 1)
	{
		write(1, "env: ", 5);
		write(1, tmp[1], ft_strlen(tmp[1]));
		write(1, ": No such file or directory\n", 28);
	}
	else
	{
		ft_putstr(comm->path);
	}
	exit(0);
}