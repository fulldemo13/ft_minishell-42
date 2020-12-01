/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:02:52 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 18:24:47 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_removestr(char **path, int pos, int len)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char **)malloc(sizeof(char*) * (len - 1))))
		return (NULL);
	while (path[i] != NULL)
	{
		if (i != pos)
		{
			tmp[j] = ft_strdup(path[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return(tmp);
}

void	ft_unset(t_com *comm)
{
	int	i;
	int	pos;
	char **tmp;

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
				tmp = ft_removestr(comm->path, pos, ft_doublestrlen(comm->path));
				clean_mem(ft_doublestrlen(comm->path), NULL, comm->path);
				comm->path = tmp;
			}
		}
		i++;
	}
}