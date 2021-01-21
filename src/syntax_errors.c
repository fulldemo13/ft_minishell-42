/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:08:25 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/21 16:22:10 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_semicolon(char *line)
{
	int		i;
	int		number;
	int 	flag;
	
	i = 0;
	number = 0;
	flag = 1;
	while (line[i] != '\0')
	{
		if (line[i] == ';' && flag == 0)
		{
			number++;
			flag++;
		}
		else if (line[i] == ';' && flag != 0)
		{
			number = -1;
			break ;
		}
		else if (!is_space(line[i]))
			flag = 0;
		i++;
	}
	return (number);
}

int		ft_quotes(char *line)
{
	int i;
	int f_simple;
	int f_double;

	i = 0;
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
		i++;
	}
	if (f_simple)
		if (f_simple % 2 != 0)
			return (0);
	if (f_double)
		if (f_double % 2 != 0)
			return (0);
	return (1);
}

int		ft_redirections(char *line)
{
	int i;
	int res;

	i = 0;
	while (line[i] != '\0')
	{
		if ((res = is_redirection(line[i])))
		{
			if (res != 3 && (is_redirection(line[i + 1]) || line[i + 1] == '\0' || is_space(line[i + 1])))
			{
				i++;
				while (is_space(line[i]))
					i++;
				if ((is_redirection(line[i]) || line[i] == '\0'))
					return (i);
			}
			else 
			{
				if (line[i] != '\0')
				{
					i++;
					if (is_space(line[i]))
					{	
						while (is_space(line[i]))
							i++;
						if ((is_redirection(line[i]) || line[i] == '\0'))
							return (i);
					}
					else
					{
						if ((is_redirection(line[i]) != 0 && is_redirection(line[i]) != 3)
							|| is_redirection(line[i + 1]) || line[i] == '\0')
							return (i);
						if (is_redirection(line[i]) == 3)
						{
							i++;
							while (is_space(line[i]))
								i++;
							if ((is_redirection(line[i]) || line[i] == '\0'))
								return (i);
						}
					}
				}
			}
		}
		if (line[i] != '\0')
		i++;
	}
	return (0);
}

int		ft_allspaces(char *line)
{
	int i;

	i = 0;

	while (line[i] != '\0')
	{
		if(!is_space(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_syntax(char *line)
{
	if(!ft_allspaces(line))
		return (1);
	else if(!ft_quotes(line))
	{
		write(1, "minishell: syntax error multiline\n", 34);
		exit_ret = 42;
		return (1);
	}
	else if(ft_semicolon(line) == -1)
	{
		write(1, "minishell: syntax error near unexpected token ';'\n", 50);
		exit_ret = 258;
		return (1);
	}
	else if(ft_redirections(line))
	{
		write(1, "minishell: syntax error near unexpected token '", 47);
		if (line[ft_redirections(line)] != '\0')
			write(1, &line[ft_redirections(line)], 1);
		else
			write(1, "newline", 7);
		write(1, "'\n", 2);
		exit_ret = 258;
		return (1);
	}
	else
		return (0);
}