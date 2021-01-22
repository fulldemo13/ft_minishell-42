/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:01:50 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/22 11:12:00 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dollar(t_com *comm, int i, int j, char *tmp)
{
	char	*name;
	char	*src = NULL;
	char	*aux;
	int		pos;
	int		k;

	j++;
	k = j;
	while (comm->words[i][k] != '\"' && comm->words[i][k] != '\0' &&
	comm->words[i][k] != '\'' && comm->words[i][k] != '$' && !is_space(comm->words[i][k]))
		k++;
	name = ft_strndup(comm->words[i] + j, k - j);
	k -= j;
	pos = ft_searchpath(comm, name);
	if (pos != -1)
	{
		aux = ft_strjoin(tmp, (comm->path[pos] + k + 1));
		free(tmp);
		tmp = aux;
	}
	if (!ft_strcmp(name, "?"))
	{
		src = ft_itoa(exit_ret);
		aux = ft_strjoin(tmp, src);
		free(tmp);
		tmp = aux;
		free(src);
	}
	free(name);
	return (tmp);
}

char	*check_home(char *word, t_com *comm)		//word es el string que vamos a buscar $
{
	int		pos;
	char	*tmp;
	char	*aux;

	pos = ft_searchpath(comm, "HOME");				//pos es la posición en que se encuentra el sting HOME=
	if (!ft_strcmp(word, "~"))
	{
		free(word);
		word = ft_strdup(comm->path[pos] + 5);		//cambiamos el guion por el path
	}
	else if (!ft_strncmp(word, "~/", 2))
	{
		tmp = ft_strdup(comm->path[pos] + 5);
		aux = word + 1;
		free(word);
		word = ft_strjoin(tmp, aux);
		free(tmp);									//concatenamos el guión  y la dirección a la que ir
	}
	return (word);
}

void 	check_quotes(t_com *comm)
{
	int 	i;
	int 	j;
	int		len;
	char	*tmp;
	char	*aux;

	i = 0;
	while (comm->words[i] != NULL)
	{
		j = 0;
		tmp = ft_strdup("");
		comm->words[i] = check_home(comm->words[i], comm);		//Mira si es alguna dirección o no
		while (comm->words[i][j] != '\0')
		{
			if (comm->words[i][j] == '\'')
			{
				j++;
				while (comm->words[i][j] != '\'' && comm->words[i][j] != '\0')
				{
					aux = ft_strnjoin(tmp, comm->words[i] + j, 1);
					free(tmp);
					tmp = aux;
					j++;
				}
				if (comm->words[i][j] != '\0')
					j++;
			}
			else if (comm->words[i][j] == '\"')
			{
				j++;
				while (comm->words[i][j] != '\"' && comm->words[i][j] != '\0')
				{	
					if (comm->words[i][j] == '$')
					{
						tmp = check_dollar(comm, i, j, tmp);
						j++;
						while (comm->words[i][j] != '\0' && comm->words[i][j] != '\"' &&
							comm->words[i][j] != '\'' && !is_space(comm->words[i][j]) && comm->words[i][j] != '$')
							j++; 
					}
					else
					{
						aux = ft_strnjoin(tmp, comm->words[i] + j, 1);
						free(tmp);
						tmp = aux;
						j++;
					}
				}
				if (comm->words[i][j] != '\0')
					j++;
			}
			else
			{
				if (comm->words[i][j] == '$')
				{
					tmp = check_dollar(comm, i, j, tmp);
					j++;
					while (comm->words[i][j] != '\0' && comm->words[i][j] != '\"' &&
						comm->words[i][j] != '\'' && !is_space(comm->words[i][j]) && comm->words[i][j] != '$')
						j++;
				}
				else
				{
					len = j;
					while (comm->words[i][len] != '\"' && comm->words[i][len] != '\0' &&
					comm->words[i][len] != '\'' && comm->words[i][len] != '$')
						len++;
					aux = ft_strnjoin(tmp, comm->words[i] + j, len - j);
					free(tmp);
					tmp = aux;
					j += len;
				}
			}
		}
		free(comm->words[i]);
		comm->words[i] = tmp;
		i++;
	}
}