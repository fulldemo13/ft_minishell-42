/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:08:25 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/12 11:04:43 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_allspaces(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int		ft_semicolon(char *line)
{
	t_div	div;

	ft_div_init(&div);
	div.flag = 1;
	while (line[div.i] != '\0')
	{
		ft_divisor_quotes(line[div.i], &div);
		if (line[div.i] == ';' && div.flag == 0
		&& !div.f_double && !div.f_simple)
		{
			div.total++;
			div.flag++;
		}
		else if (line[div.i] == ';' && div.flag != 0
		&& !div.f_double && !div.f_simple)
		{
			div.total = -1;
			break ;
		}
		else if (!ft_isspace(line[div.i])
		&& !div.f_double && !div.f_simple)
			div.flag = 0;
		div.i++;
	}
	return (div.total);
}

int		ft_quotes(char *line)
{
	t_div	div;

	ft_div_init(&div);
	while (line[div.i] != '\0')
	{
		ft_divisor_quotes(line[div.i], &div);
		div.i++;
	}
	if (div.f_simple)
		if (div.f_simple % 2 != 0)
			return (0);
	if (div.f_double)
		if (div.f_double % 2 != 0)
			return (0);
	return (1);
}

void	ft_redirection_syntax(char *line)
{
	write(1, "minishell: syntax error near unexpected token '", 47);
	if (line[ft_redirections(line)] != '\0')
		write(1, &line[ft_redirections(line)], 1);
	else
		write(1, "newline", 7);
	write(1, "'\n", 2);
}

int		ft_check_syntax(char *line)
{
	if (!ft_allspaces(line))
		return (1);
	else if (!ft_quotes(line))
	{
		write(1, "minishell: syntax error multiline\n", 34);
		g_exit_ret = 42;
		return (1);
	}
	else if (ft_semicolon(line) == -1)
	{
		write(1, "minishell: syntax error near unexpected token ';'\n", 50);
		g_exit_ret = 258;
		return (1);
	}
	else if (ft_redirections(line))
	{
		ft_redirection_syntax(line);
		g_exit_ret = 258;
		return (1);
	}
	return (0);
}
