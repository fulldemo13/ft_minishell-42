/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 09:27:37 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 10:08:45 by fulldemo         ###   ########.fr       */
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
				return(i);
			else if (comm->path[i][j] != words[j])
				break ;
			j++;
		}
		i++;
	}
	free(words);
	return (-1);
}

char	**ft_getbinpath(t_com *comm)
{
	int		pos;
	int		i;
	char	*bin_path;
	char	**tmp;

	i = 0;
	pos = ft_searchpath(comm, "PATH");
	while (comm->path[pos][i] != '=')
		i++;
	i++;
	bin_path = ft_strdup(comm->path[pos] + i);	//guarda todo el contenido de PATH=

	tmp = ft_split(bin_path, ':');				//añadir / al final del string
	free(bin_path);
	bin_path[0] = '\0';
	i = 0;
	while (tmp[i] != NULL)
	{
		bin_path = ft_strjoin(tmp[i], "/");
		free(tmp[i]);
		tmp[i] = bin_path;
		i++;
	}
	return(tmp);
}