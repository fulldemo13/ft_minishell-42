/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublestrdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:54:02 by fulldemo          #+#    #+#             */
/*   Updated: 2020/02/21 16:00:16 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_doublestrlen(char **s)
{
	int i;

	i  = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_doublestrdup(char **str, int i)
{
	char 	**ret;
	int		j;

	j = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	while (i > j)
	{
		ret[j] = ft_strdup(str[j]);
		j++;
	}
	return(ret);
}