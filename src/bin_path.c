/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 09:27:37 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/04 16:47:00 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**ft_getbinpath(t_com *comm)
{
	int		pos;
	int		i;
	char	*bin_path;
	char	**tmp;

	i = 0;
	comm->number_bin_path = 1;
	pos = ft_searchpath(comm, "PATH");
	while (comm->path[pos][i] != '=')
		i++;
	i++;
	bin_path = ft_strdup(comm->path[pos] + i);
	i = 0;
	while (bin_path[i])
		if (bin_path[i++] == ':')
			comm->number_bin_path++;
	tmp = ft_split(bin_path, ':');
	free(bin_path);
	bin_path[0] = '\0';
	i = 0;
	while (comm->number_bin_path > i)
	{
		bin_path = ft_strjoin(tmp[i], "/");
		free(tmp[i]);
		tmp[i] = bin_path;
		i++;
	}
	return(tmp);
}