/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:57:56 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 15:44:58 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd(t_com *comm)
{
	char	*tmp;
	char	*aux;
	int		pos;

	if (ft_doublestrlen(comm->words) == 1)
	{
		tmp = ft_strdup("/Users/");
		pos = ft_searchpath(comm, "USER");
		aux = ft_strjoin(tmp, comm->path[pos] + 5);
		free(tmp);
		tmp = aux;
		chdir(tmp);
		free(tmp);
		exit_ret = 0;
	}
	else if ((chdir(comm->words[1])) == -1)
	{
		write(1, "minishell: ", 12);
		write(1, comm->words[1], ft_strlen(comm->words[1]));
		write(1, ": No such file or directory\n", 28);
		exit_ret = 1;
	}
}
