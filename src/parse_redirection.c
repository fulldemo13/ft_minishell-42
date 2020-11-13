/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:57:00 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/02 16:06:28 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_redirection(t_com *comm)
{
	int		i;
	int		j;
	int		flag;
	char	**tmp;
	char 	*aux;
	char	*s;
	int		large;

	i = 0;
	large = 0;
	flag = 0;
	aux = ft_strdup("");
	if (!(tmp = (char **)malloc(sizeof(char*))))
		return (NULL);
	while (comm->number_words > i)
	{
		if (comm->words[i][0] == '\'' || comm->words[i][0] == '\"')
		{
			tmp = ft_addstr(tmp, large, comm->words[i]);
			large++;
		}
		else
		{
			j = 0;
			while (comm->words[i][j] != '\0')
			{
				if (!is_redirection(comm->words[i][j]) && comm->words[i][j] != '\0')
				{
					while (!is_redirection(comm->words[i][j]) && comm->words[i][j] != '\0')
					{
						s = ft_strnjoin(aux, comm->words[i] + j, 1);
						free(aux);
						aux = s;
						j++;
					}
					tmp = ft_addstr(tmp, large, aux);
					free(aux);
					aux = ft_strdup("");
					large++;
				}
				if (is_redirection(comm->words[i][j]))
				{
					while (is_redirection(comm->words[i][j]) && comm->words[i][j] != '\0')
					{
						s = ft_strnjoin(aux, comm->words[i] + j, 1);
						free(aux);
						aux = s;
						j++;
					}
					tmp = ft_addstr(tmp, large, aux);
					free(aux);
					aux = ft_strdup("");
					large++;
				}
			}
		}
		i++;
	}
	free(aux);
	comm->number_words = large;
	return (tmp);
}