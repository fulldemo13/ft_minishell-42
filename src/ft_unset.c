/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:02:52 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/05 17:51:37 by fulldemo         ###   ########.fr       */
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
	while (len > i)
	{
		if (i != pos)
		{
			tmp[j] = ft_strdup(path[i]);
			j++;
		}
		i++;
	}
	clean_mem(len, NULL, path);
	return(tmp);
}

void	ft_unset(t_com *comm)
{
	int	i;
	int	pos;

	i = 1;
	while (comm->number_words > i)
	{
		if (ft_strchr(comm->words[i], '='))
		{
			write(1,"minishell: ",11);
			write(1, comm->words[i], ft_strlen(comm->words[i]));
			write(1, ": not a valid identifier\n", 25);
			exit_ret = -1;
		}
		else
		{
			pos = ft_searchpath(comm, comm->words[i]);
			if (pos != -1)
			{
				comm->path = ft_removestr(comm->path, pos, comm->number_path);
				comm->number_path--;
			}
		}
		i++;
	}
	if (exit_ret == -1)
		exit_ret = 1;
	else
		exit_ret = 0;
}