/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:23 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 12:51:52 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_exec_dup2(int *fd, int i, int j)
{
	dup2(fd[i], j);
	ft_close_pipes(fd);
}

char	**ft_relode_binpath_getexe(t_com *comm, int i, int j)
{
	ft_clean_mem(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);
	return (ft_to_execute(comm, i, j));
}

char	**ft_to_execute(t_com *comm, int i, int j)
{
	char	**tmp;
	int		k;
	int		m;

	k = 0;
	m = i - j;
	if (!(tmp = (char **)malloc(sizeof(char *) * (m + 1))))
		return (NULL);
	while (k < m)
	{
		tmp[k] = ft_strdup(comm->words[j]);
		j++;
		k++;
	}
	tmp[k] = NULL;
	return (tmp);
}

void	ft_exec_comm(t_com *comm, char **tmp, int *fd)
{
	int		i;
	char	*aux;
	int		res;
	
	i = 0;
	if ((res = execve(tmp[0], tmp, comm->path)) == -1)
	{
		aux = ft_strjoin(comm->bin_path[i], tmp[0]);
		while ((res = execve(aux, tmp, comm->path) == -1))
		{
			i++;
			free(aux);
			aux = ft_strjoin(comm->bin_path[i], tmp[0]);
			if (i == ft_doublestrlen(comm->bin_path) - 1)
				ft_notfound(comm->words[0], fd);
		}
		free(aux);
	}
}