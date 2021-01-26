/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:01:50 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 16:33:06 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exit_dollar(char *tmp)
{
	char	*src;
	char	*aux;

	src = ft_itoa(exit_ret);
	aux = ft_strjoin(tmp, src);
	free(tmp);
	tmp = aux;
	free(src);
	return (tmp);
}

char	*check_dollar(t_com *comm, int i, int j, char *tmp)
{
	char	*name;
	char	*aux;
	int		pos;
	int		k;

	j++;
	k = j;
	while (comm->words[i][k] != '\"' && comm->words[i][k] != '\0' &&
	comm->words[i][k] != '\'' && comm->words[i][k] != '$' &&
	!ft_isspace(comm->words[i][k]))
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
		tmp = ft_exit_dollar(tmp);
	free(name);
	return (tmp);
}

char	*check_home(char *word, t_com *comm)
{
	int		pos;
	char	*tmp;
	char	*aux;

	pos = ft_searchpath(comm, "HOME");
	if (!ft_strcmp(word, "~"))
	{
		free(word);
		word = ft_strdup(comm->path[pos] + 5);
	}
	else if (!ft_strncmp(word, "~/", 2))
	{
		tmp = ft_strdup(comm->path[pos] + 5);
		aux = word + 1;
		free(word);
		word = ft_strjoin(tmp, aux);
		free(tmp);
	}
	return (word);
}
