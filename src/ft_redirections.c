/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:59:43 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/26 16:32:23 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_next_space(char *line, t_div *div)
{
	while (ft_isspace(line[div->i]))
		div->i++;
	if ((is_redirection(line[div->i]) || line[div->i] == '\0'))
		return (1);
	return (0);
}

int		ft_next_redirection(char *line, t_div *div)
{
	if (ft_isspace(line[div->i]))
	{
		if (ft_next_space(line, div))
			return (1);
	}
	else
	{
		if ((is_redirection(line[div->i]) != 0 &&
		is_redirection(line[div->i]) != 3) ||
		is_redirection(line[div->i + 1]) || line[div->i] == '\0')
			return (1);
		if (is_redirection(line[div->i]) == 3)
		{
			div->i++;
			if (ft_next_space(line, div))
				return (1);
		}
	}
	return (0);
}

int		ft_redirections_check(char *line, t_div *div)
{
	if (div->total != 3 && (is_redirection(line[div->i + 1]) ||
	line[div->i + 1] == '\0'
	|| ft_isspace(line[div->i + 1])))
	{
		div->i++;
		if (ft_next_space(line, div))
			return (1);
	}
	else
	{
		if (line[div->i] != '\0')
		{
			div->i++;
			if (ft_next_redirection(line, div))
				return (1);
		}
	}
	return (0);
}

int		ft_redirections(char *line)
{
	t_div	div;

	ft_div_init(&div);
	while (line[div.i] != '\0')
	{
		if ((div.total = is_redirection(line[div.i])))
		{
			if (ft_redirections_check(line, &div))
				return (div.i);
		}
		line[div.i] != '\0' ? div.i++ : 0;
	}
	return (0);
}
