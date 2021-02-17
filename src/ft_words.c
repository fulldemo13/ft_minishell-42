/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:56:51 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/12 11:05:15 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_malloc_words_reditection(char *line, char **words, t_div *div)
{
	if ((!ft_isspace(line[div->i])) || (div->f_double != 0 ||
	div->f_simple != 0))
	{
		div->flag = 0;
		div->f_redirection++;
	}
	if (div->f_double == 0 && div->f_simple == 0 &&
	((ft_isspace(line[div->i]) && !div->flag) || ((!ft_isspace(line[div->i])
	&& !is_redirection(line[div->i])) && (line[div->i + 1] == '\0' ||
	is_redirection(line[div->i + 1]))) || (is_redirection(line[div->i]) &&
	!is_redirection(line[div->i + 1]))))
	{
		if (!(words[div->total] = (char *)malloc(sizeof(char) *
		(div->f_redirection + 1))))
			return (1);
		div->total++;
		div->flag++;
		div->f_redirection = 0;
	}
	return (0);
}

int		ft_malloc_words(char *line, char **words)
{
	t_div	div;

	ft_div_init(&div);
	div.flag = 1;
	(void)words;
	while (line[div.i] != '\0')
	{
		ft_divisor_quotes(line[div.i], &div);
		if (ft_malloc_words_reditection(line, words, &div))
			return (1);
		div.i++;
	}
	return (0);
}

void	ft_fill_words_redirection(char *line, char **words, t_div *div)
{
	if ((!ft_isspace(line[div->i])) || (div->f_double != 0 ||
	div->f_simple != 0))
	{
		div->flag = 0;
		words[div->total][div->f_redirection] = line[div->i];
		div->f_redirection++;
	}
	if (div->f_double == 0 && div->f_simple == 0 && ((ft_isspace(line[div->i])
	&& !div->flag) || ((!ft_isspace(line[div->i]) &&
	!is_redirection(line[div->i])) && (line[div->i + 1] == '\0' ||
	is_redirection(line[div->i + 1]))) || (is_redirection(line[div->i]) &&
	!is_redirection(line[div->i + 1]))))
	{
		words[div->total][div->f_redirection] = '\0';
		div->total++;
		div->flag++;
		div->f_redirection = 0;
	}
}

int		ft_fill_words(char *line, char **words)
{
	t_div	div;

	ft_div_init(&div);
	div.flag = 1;
	(void)words;
	while (line[div.i] != '\0')
	{
		ft_divisor_quotes(line[div.i], &div);
		ft_fill_words_redirection(line, words, &div);
		div.i++;
	}
	words[div.total] = NULL;
	return (0);
}
