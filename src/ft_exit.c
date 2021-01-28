/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 11:57:20 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/28 09:58:49 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_sig_exit(int i)
{
	i = 0;
	write(1, "\x1b[31mexit\x1b[0m\n", 14);
	return (0);
}

void	ft_prompt_exit(char *line, int mode)
{
	write(1, "minishell: ", 12);
	write(1, "exit: ", 6);
	if (line)
		write(1, line, ft_strlen(line));
	if (mode)
		write(1, ": numeric argument required\n", 28);
	else
		write(1, ": too many commands\n", 20);
}

int		ft_exit_number(char *line)
{
	int i;

	i = ft_atoi(line);
	while (i >= 256)
		i -= 256;
	return (i);
}

int		ft_exit(t_com *comm)
{
	int		i;

	i = 0;
	write(1, "\x1b[31mexit\x1b[0m\n", 14);
	if (ft_doublestrlen(comm->words) > 2)
	{
		ft_prompt_exit(NULL, 0);
		g_exit_ret = 1;
		return (-1);
	}
	else if (ft_doublestrlen(comm->words) == 2)
	{
		while (comm->words[1][i] != '\0')
		{
			if (!ft_isdigit(comm->words[1][i]))
			{
				ft_prompt_exit(comm->words[1], 1);
				return (255);
			}
			i++;
		}
		return (ft_exit_number(comm->words[1]));
	}
	return (0);
}
