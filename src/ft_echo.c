/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:42:06 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/02 18:23:22 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(t_com *comm)
{
	int i;
	int	ret;

	ret = 0;
	i = 1;
	if (comm->number_words > i)
		if ((ret = ft_strcmp(comm->words[i], "-n")) == 0)
			i++;
	while ((comm->number_words > i))
	{
		write(global_fd, comm->words[i], ft_strlen(comm->words[i]));
		i++;
		if (comm->number_words > i)
				write(global_fd, " ", 1);
	}
	if (ret)
		write(global_fd, "\n", 1);
	exit_ret = 0;
}