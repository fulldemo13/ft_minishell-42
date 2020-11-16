/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:57:00 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/16 18:36:39 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_count_redirection(t_com *comm)
{
	int		i;
	int		j;
	int		flag;
	int		res;

	i = 0;
	flag = 0;
	res = 0;
	while (comm->words[i] != NULL)
	{
		if (comm->words[i][0] == '\'' || comm->words[i][0] == '\"')
		{
			res++;
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
						j++;
					}
					res++;
				}
				else if (is_redirection(comm->words[i][j]))
				{
					while (is_redirection(comm->words[i][j]) && comm->words[i][j] != '\0')
					{
						j++;
					}
					res++;
				}
			}
		}
		i++;
	}
	printf("redirections:%i\n", res);
	return (res);
}

char	**parse_redirection(t_com *comm)
{
	int		i;
	int		j;
	int		k;
	int		flag;
	char	**tmp;
	char 	*aux;
	char	*s;
	
	i = 0;
	k = 0;
	flag = 0;
	aux = ft_strdup("");
	if (!(tmp = (char **)malloc(sizeof(char*) * (ft_count_redirection(comm) + 1))))
		return (NULL);
	while (comm->words[i] != NULL)
	{
		if (comm->words[i][0] == '\'' || comm->words[i][0] == '\"')
		{
			tmp[k] = ft_strdup(comm->words[i]);
			k++;
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
					tmp[k] = ft_strdup(aux);
					free(aux);
					aux = ft_strdup("");
					k++;
				}
				else if (is_redirection(comm->words[i][j]))
				{
					while (is_redirection(comm->words[i][j]) && comm->words[i][j] != '\0')
					{
						s = ft_strnjoin(aux, comm->words[i] + j, 1);
						free(aux);
						aux = s;
						j++;
					}
					tmp[k] = ft_strdup(aux);
					k++;
					free(aux);
					aux = ft_strdup("");
				}
			}
		}
		i++;
	}
	tmp[k] = NULL;
	free(aux);
	clean_mem2(comm->words);
	return (tmp);
}