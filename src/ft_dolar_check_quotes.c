/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolar_check_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:43:16 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 15:55:12 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_singlequote(t_com *comm, t_quo *quo)
{
	quo->j++;
	while (comm->words[quo->i][quo->j] != '\'' &&
	comm->words[quo->i][quo->j] != '\0')
	{
		quo->aux = ft_strnjoin(quo->tmp, comm->words[quo->i] + quo->j, 1);
		free(quo->tmp);
		quo->tmp = quo->aux;
		quo->j++;
	}
	if (comm->words[quo->i][quo->j] != '\0')
		quo->j++;
}

void	ft_doublequote(t_com *comm, t_quo *quo)
{
	quo->j++;
	while (comm->words[quo->i][quo->j] != '\"' &&
	comm->words[quo->i][quo->j] != '\0')
	{
		if (comm->words[quo->i][quo->j] == '$')
		{
			quo->tmp = check_dollar(comm, quo->i, quo->j, quo->tmp);
			quo->j++;
			while (comm->words[quo->i][quo->j] != '\0' &&
			comm->words[quo->i][quo->j] != '\"' &&
			comm->words[quo->i][quo->j] != '\'' &&
			!is_space(comm->words[quo->i][quo->j]) &&
			comm->words[quo->i][quo->j] != '$')
				quo->j++;
		}
		else
		{
			quo->aux = ft_strnjoin(quo->tmp, comm->words[quo->i] + quo->j, 1);
			free(quo->tmp);
			quo->tmp = quo->aux;
			quo->j++;
		}
	}
	if (comm->words[quo->i][quo->j] != '\0')
		quo->j++;
}

void	ft_dollarend(t_com *comm, t_quo *quo)
{
	if (comm->words[quo->i][quo->j] == '$')
	{
		quo->tmp = check_dollar(comm, quo->i, quo->j, quo->tmp);
		quo->j++;
		while (comm->words[quo->i][quo->j] != '\0' &&
		comm->words[quo->i][quo->j] != '\"' &&
		comm->words[quo->i][quo->j] != '\'' &&
		!is_space(comm->words[quo->i][quo->j]) &&
		comm->words[quo->i][quo->j] != '$')
			quo->j++;
	}
	else
	{
		quo->len = quo->j;
		while (comm->words[quo->i][quo->len] != '\"' &&
		comm->words[quo->i][quo->len] != '\0' &&
		comm->words[quo->i][quo->len] != '\'' &&
		comm->words[quo->i][quo->len] != '$')
			quo->len++;
		quo->aux = ft_strnjoin(quo->tmp, comm->words[quo->i] + quo->j,
		quo->len - quo->j);
		free(quo->tmp);
		quo->tmp = quo->aux;
		quo->j += quo->len;
	}
}

void	ft_check_quotes_dolar(t_com *comm)
{
	t_quo	quo;

	quo.i = 0;
	while (comm->words[quo.i] != NULL)
	{
		quo.j = 0;
		quo.tmp = ft_strdup("");
		comm->words[quo.i] = check_home(comm->words[quo.i], comm);
		while (comm->words[quo.i][quo.j] != '\0')
		{
			if (comm->words[quo.i][quo.j] == '\'')
				ft_singlequote(comm, &quo);
			else if (comm->words[quo.i][quo.j] == '\"')
				ft_doublequote(comm, &quo);
			else
				ft_dollarend(comm, &quo);
		}
		free(comm->words[quo.i]);
		comm->words[quo.i] = quo.tmp;
		quo.i++;
	}
}
