/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divisor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:56:51 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/17 10:46:37 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_divisor(char *line)
{
	int 	total;
	int 	i;
	int 	f_simple;
	int 	f_double;
	int		f_redirection;
	int		flag;

	i = 0;
	flag = 0;
	total = 0;
	f_simple = 0;
	f_double = 0;
	f_redirection = 0;
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
		if (is_redirection(line[i]) && f_redirection == 0 && f_double == 0 && f_simple == 0)
		{
			flag = 0;
			f_redirection = 1;
			total++;
		}
		if (!is_space(line[i]) && flag == 0 && !is_redirection(line[i]))
		{
			flag = 1;
			f_redirection = 0;
			total++;
		}
		if (is_space(line[i]) && f_double == 0 && f_simple == 0)
		{
			flag = 0;
			f_redirection = 0;
		}
		i++;
	}
	return (total);
}

int ft_malloc_words(char *line, char **words)
{	
	int		i;
	int		j;
	int 	f_simple;
	int 	f_double;
	int		letter;
	int		flag;

	i = 0;
	j = 0;
	letter = 0;
	flag = 1;
	f_simple = 0;
	f_double = 0;

	(void)words;

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
		if ((!is_space(line[i])) || (f_double != 0 || f_simple != 0))
		{
			flag = 0;
			letter++;
		}
		if (f_double == 0 && f_simple == 0 && ((is_space(line[i]) && !flag)
			|| ((!is_space(line[i]) && !is_redirection(line[i])) && (line[i + 1] == '\0' || is_redirection(line[i + 1])))
			|| (is_redirection(line[i]) && !is_redirection(line[i + 1]))))
		{
			if (!(words[j] = (char *)malloc(sizeof(char) * (letter + 1))))
				return (0);
			j++;
			flag++;
			letter = 0;
		}
		i++;
	}
	return (1);
}

int ft_fill_words(char *line, char **words)
{	
	int		i;
	int		j;
	int		k;
	int 	f_simple;
	int 	f_double;
	int		flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 1;
	f_simple = 0;
	f_double = 0;

	(void)words;

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
		if ((!is_space(line[i])) || (f_double != 0 || f_simple != 0))
		{
			flag = 0;
			words[j][k] = line[i];
			k++;
		}
		if (f_double == 0 && f_simple == 0 && ((is_space(line[i]) && !flag)
			|| ((!is_space(line[i]) && !is_redirection(line[i])) && (line[i + 1] == '\0' || is_redirection(line[i + 1])))
			|| (is_redirection(line[i]) && !is_redirection(line[i + 1]))))
		{
			words[j][k] = '\0';
			j++;
			flag++;
			k = 0;
		}
		i++;
	}
	words[j] = NULL;
	return (1);
}