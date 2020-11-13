/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:33:20 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/07 17:00:36 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fd(t_com *comm)
{
	int		i;
	int		start;
	char	**tmp;
	int		flag;

	i = 0;
	start = 0;
	flag = 0;
	while (comm->number_words > i)
	{
		if (!ft_strcmp(comm->words[i], ">"))
		{	
			i++;
			flag = 1;
			if (comm->number_words > i)
				global_fd = open(comm->words[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		if (!ft_strcmp(comm->words[i], ">>"))
		{	
			i++;
			flag = 1;
			if (comm->number_words > i)
				global_fd = open(comm->words[i], O_WRONLY | O_CREAT | O_APPEND , 0777);
		}
	/*	if (!ft_strcmp(comm->words[i], "<"))
		{
		
		}*/
		i++;
		if (flag == 0)
			start++;
	}
	if (start != comm->number_words)
	{
		while (start < comm->number_words)
		{
			tmp = ft_removestr(comm->words, start, comm->number_words);
			comm->number_words--;
			comm->words = tmp;
		}
	}
}