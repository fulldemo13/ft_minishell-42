/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublestrdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:54:02 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 09:40:32 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_doublestrlen(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

char	**ft_doublestrdup(char **str)
{
	char	**ret;
	int		i;

	i = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1))))
		return (NULL);
	while (str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
