/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:20:18 by fulldemo          #+#    #+#             */
/*   Updated: 2020/02/09 19:24:22 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_line(char **mem, char **line, int i)
{
	char *aux1;
	char *aux2;

	if (!*mem && !i)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if ((aux1 = ft_strchr(*mem, '\n')))
	{
		*aux1 = 0;
		*line = ft_strdup(*mem);
		aux2 = ft_strdup(++aux1);
		free(*mem);
		*mem = aux2;
	}
	else
	{
		*line = ft_strdup(*mem);
		*mem = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(char **line)
{
	static char	*memory[4096];
	char		buffer[129];
	int			i;
	char		*aux;

	if (!line)
		return (-1);
	while (ft_strchr(*memory, '\n') == NULL)
	{
		i = read(0, buffer, 128);
		if (i < 0)
			return (-1);
		if (i == 0)
			break ;
		buffer[i] = '\0';
		if (*memory == '\0')
			*memory = ft_strdup(buffer);
		else
		{
			aux = ft_strjoin(*memory, buffer);
			free(*memory);
			*memory = aux;
		}
	}
	return (get_line(memory, line, i));
}
