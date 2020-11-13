/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 08:17:03 by fulldemo          #+#    #+#             */
/*   Updated: 2020/02/29 09:59:04 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		divider(char *line)
{
	int		i;
	int		words;
	int		flag;
	int 	f_simple;
	int 	f_double;

	i = 0;
	flag = 0;
	words = 0;
	f_simple = 0;
	f_double = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && f_double == 0)
		{
			if (!f_simple)
				f_simple++;
			else
				f_simple = 0;
		}
		if (line[i] == '\"' &&  f_simple == 0)
		{
			if (!f_double)
				f_double++;
			else
				f_double = 0;
		}
		if (!is_space(line[i]) && flag == 0)
		{
			flag = 1;
			words++;
		}
		if (is_space(line[i]) && f_double == 0 && f_simple == 0)
			flag = 0;
		i++;
	}
	return (words);
}

void	fill_commands(char *line, char **commands)
{
	int	i;
	int	j;
	int	k;
	int	flag;
	int 	f_simple;
	int 	f_double;

	i = 0;
	j = 0;
	k = 0;
	flag = 1;
	f_simple = 0;
	f_double = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && f_double == 0)
		{
			if (!f_simple)
				f_simple++;
			else
				f_simple = 0;
		}
		if (line[i] == '\"' &&  f_simple == 0)
		{
			if (!f_double)
				f_double++;
			else
				f_double = 0;
		}
		if (!is_space(line[i]) || (f_double != 0 || f_simple != 0))
		{
			commands[k][j] = line[i];
			flag = 0;
			j++;
		}
		if ((is_space(line[i]) && flag == 0 && f_double == 0 && f_simple == 0) || (line[i + 1] == '\0' && !is_space(line[i])))
		{
			commands[k][j] = '\0';
			k++;
			flag++;
			j = 0;
		}
		i++;
	}
}

int		malloc_commands(char *line, char **commands, int let, int flag)
{
	int		i;
	int		j;
	int 	f_simple;
	int 	f_double;

	i = 0;
	j = 0;
	let = 0;
	flag = 1;
	f_simple = 0;
	f_double = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && f_double == 0)
		{
			if (!f_simple)
				f_simple++;
			else
				f_simple = 0;
		}
		if (line[i] == '\"' &&  f_simple == 0)
		{
			if (!f_double)
				f_double++;
			else
				f_double = 0;
		}
		if (!is_space(line[i]) || (f_double != 0 || f_simple != 0))
		{
			flag = 0;
			let++;
		}
		if ((is_space(line[i]) && !flag && f_double == 0 && f_simple == 0)
			|| (!is_space(line[i]) && line[i + 1] == '\0'))
		{
			if (!(commands[j] = (char *)malloc(sizeof(char) * (let + 1))))
				return (0);
			j++;
			flag++;
			let = 0;
		}
		i++;
	}
	return (1);
}

char	**get_commands(char *line)
{
	char	**commands;
	int		words;
	int		flag;
	int		let;

	let = 0;
	flag = 0;
	words = divider(line);
	if (!(commands = (char **)malloc(sizeof(char *) * (words))))
		return (NULL);
	if (!malloc_commands(line, commands, let, flag))
		return (NULL);
	fill_commands(line, commands);
	return (commands);
}