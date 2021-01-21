/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:02:52 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/21 15:54:36 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_removestr(t_com *comm, int pos)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char*) * (ft_doublestrlen(comm->path)))))
		return (1);
	while (comm->path[i] != NULL)
	{
		if (i != pos)
		{
			tmp[j] = comm->path[i];
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	free(comm->path[pos]);
	free(comm->path);
	comm->path = tmp;
	return(0);
}

void	ft_unset(t_com *comm)
{
	int	i;
	int	pos;

	i = 1;
	while (comm->words[i] != NULL)
	{
		if (ft_strchr(comm->words[i], '='))
		{
			write(1,"minishell: ",11);
			write(1, comm->words[i], ft_strlen(comm->words[i]));
			write(1, ": not a valid identifier\n", 25);
		}
		else
		{
			pos = ft_searchpath(comm, comm->words[i]);
			if (pos != -1)
			{
				ft_removestr(comm, pos);
			}
		}
		i++;
	}
	exit_ret = 0;
}