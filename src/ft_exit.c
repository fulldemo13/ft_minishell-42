/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 11:57:20 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/22 15:42:33 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_sig_exit()
{
	write(1, "\x1b[31mexit\x1b[0m\n", 14);
	return (0);
}

int		ft_exit(t_com *comm)
{
	int		i;

	i = 0;
	if (ft_doublestrlen(comm->words) > 2)
	{
		write(1, "\x1b[31mexit\x1b[0m\n", 14);
		write(1, "minishell: ", 12);
		write(1, comm->words[0], ft_strlen(comm->words[0]));
		write(1, ": too many commands\n", 20);
		exit_ret = 1;
		return (-1);
	}
	else if (ft_doublestrlen(comm->words) == 2)
	{
		while (comm->words[1][i] != '\0')
		{
			if (!ft_isdigit(comm->words[1][i]))
			{
				write(1, "\x1b[31mexit\x1b[0m\n", 14);
				write(1, "minishell: ", 12);
				write(1, "exit: ", 6);
				write(1, comm->words[1], ft_strlen(comm->words[1]));
				write(1, ": numeric argument required\n", 28);
				return(255);
			}
			i++;	
		}
		i = ft_atoi(comm->words[1]);
		while (i >= 256)
			i -= 256;
		write(1, "\x1b[31mexit\x1b[0m\n", 14);
		return(i);
	}
	else
	{
		write(1, "\x1b[31mexit\x1b[0m\n", 14);
		return (0);
	}
}