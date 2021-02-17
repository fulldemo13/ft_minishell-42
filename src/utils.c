/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:17:10 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/07 09:23:13 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redirection(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (3);
	else if (c == '|')
		return (2);
	return (0);
}

void	ft_clean_mem(char **commands)
{
	int i;

	i = 0;
	if (commands)
	{
		while (commands[i] != NULL)
		{
			free(commands[i]);
			commands[i] = NULL;
			i++;
		}
		free(commands);
	}
	commands = NULL;
}

void	ft_putstr(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		write(1, str[i], ft_strlen(str[i]));
		write(1, "\n", 1);
		i++;
	}
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	if (len > ft_strlen(s2))
		len = ft_strlen(s2);
	if (!(src = malloc(sizeof(char) * (ft_strlen(s1) + len + 1))))
		return (NULL);
	while (s1[i])
	{
		src[i] = s1[i];
		i++;
	}
	while (len > 0)
	{
		src[i] = s2[j];
		j++;
		i++;
		len--;
	}
	src[i] = '\0';
	return (src);
}

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	i;
	char	*r;

	i = 0;
	while (s1[i] != '\0' && i < len)
		i++;
	r = malloc(i + 1);
	if (r == NULL)
	{
		return (0);
	}
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
