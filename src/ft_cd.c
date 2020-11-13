/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:57:56 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/06 16:09:02 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd(t_com *comm)
{
	char	*tmp;
	char	*aux;
	int		pos;
//	int		i;

/*	if (comm->number_words >= 2)
		if (!ft_strcmp(comm->words[1], "<"))
		{
			i = comm->number_words;
			comm->number_words = 1;
		}*/
	if (comm->number_words == 1)
	{
	//	comm->number_words = i;
		tmp = ft_strdup("/Users/");
		pos = ft_searchpath(comm, "USER");
		aux = ft_strjoin(tmp, comm->path[pos] + 5);
		free(tmp);
		tmp = aux;
		chdir(tmp);
		free(tmp);
		exit_ret = 1;
	}
	else if((chdir(comm->words[1])) == -1)
	{
		write(global_fd, "minishell: ", 12);
		write(global_fd, comm->words[1], ft_strlen(comm->words[1]));
		write(global_fd, ": No such file or directory\n", 28);
		exit_ret = 1;
	}
	else
		exit_ret = 0;
}