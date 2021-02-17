/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:44:54 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/12 11:05:37 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_div_init(t_div *div)
{
	div->i = 0;
	div->total = 0;
	div->flag = 0;
	div->f_simple = 0;
	div->f_double = 0;
	div->f_redirection = 0;
}

void	ft_divisor_quotes(char c, t_div *div)
{
	if (c == '\'' && div->f_double == 0)
	{
		if (!div->f_simple)
			div->f_simple++;
		else
			div->f_simple = 0;
	}
	if (c == '\"' && div->f_simple == 0)
	{
		if (!div->f_double)
			div->f_double++;
		else
			div->f_double = 0;
	}
}

void	ft_divisor_redirection(char *line, t_div *div)
{
	if (is_redirection(line[div->i]) && div->f_redirection == 0 &&
	div->f_double == 0 && div->f_simple == 0)
	{
		div->flag = 0;
		div->f_redirection = 1;
		div->total++;
	}
	if (!ft_isspace(line[div->i]) && div->flag == 0 &&
	!is_redirection(line[div->i]))
	{
		div->flag = 1;
		div->f_redirection = 0;
		div->total++;
	}
	if (ft_isspace(line[div->i]) && div->f_double == 0 && div->f_simple == 0)
	{
		div->flag = 0;
		div->f_redirection = 0;
	}
}

int		ft_divisor(char *line)
{
	t_div	div;

	ft_div_init(&div);
	while (line[div.i] != '\0')
	{
		ft_divisor_quotes(line[div.i], &div);
		ft_divisor_redirection(line, &div);
		div.i++;
	}
	return (div.total);
}
