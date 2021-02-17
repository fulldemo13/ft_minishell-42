/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 09:27:37 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/07 11:12:17 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_searchpath(t_com *comm, char *words)
{
	int	i;
	int	j;

	i = 0;
	while (comm->path[i] != NULL)
	{
		j = 0;
		while (comm->path[i][j] != '\0')
		{
			if (comm->path[i][j] == '=' && words[j] == '\0')
				return (i);
			else if (comm->path[i][j] != words[j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

char	**ft_fill_binpath(char **tmp, char *bin_path)
{
	int i;

	i = 0;
	while (tmp[i] != NULL)
	{
		bin_path = ft_strjoin(tmp[i], "/");
		free(tmp[i]);
		tmp[i] = bin_path;
		i++;
	}
	return (tmp);
}

char	**ft_getbinpath(t_com *comm)
{
	int		pos;
	int		i;
	char	*bin_path;
	char	**tmp;

	i = 0;
	if ((pos = ft_searchpath(comm, "PATH")) == -1)
	{
		ft_notfound(comm->words[0], 0);
		return (NULL);
	}
	while (comm->path[pos][i] != '=')
		i++;
	i++;
	bin_path = ft_strdup(comm->path[pos] + i);
	tmp = ft_split(bin_path, ':');
	free(bin_path);
	bin_path[0] = '\0';
	return (ft_fill_binpath(tmp, bin_path));
}
