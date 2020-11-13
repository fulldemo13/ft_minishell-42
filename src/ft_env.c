/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 09:22:03 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/05 17:50:35 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_com *comm)
{
	if (comm->number_words > 1)
	{
		write(1, "env: ", 5);
		write(1, comm->words[1], ft_strlen(comm->words[1]));
		write(1, ": No such file or directory\n", 28);
		exit_ret = 127;
	}
	else
	{
		ft_putstr(comm->path, comm->number_path);
		exit_ret = 0;
	}
}