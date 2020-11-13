/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:53:31 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/13 17:36:47 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putquote(char **str, int len)
{
	int	i;
	int j;
	int flag;

	j = 0;
	flag = 0;
	while (len > j)
	{
		write(global_fd, "declare -x ", 11);
		i = 0;
		while (str[j][i] != '\0')
		{
			flag = 0;
			write(global_fd, &str[j][i], 1);
			if (str[j][i] == '=' && !flag)
			{
				write(global_fd, "\"", 2);
				flag++;
			}
			i++;
		}
		j++;
		write(global_fd, "\"\n", 2);
	}
}

char	**ft_addstr(char **str, char *new)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char*) * (ft_doublestrlen(str) + 1))))
		return (0);
	while (str[i] != NULL)
	{
		tmp[i] = ft_strdup(str[i]);
		i++;
	}
	tmp[i] = ft_strdup(new);
	i += 1;
	tmp[i] = NULL;
	return (tmp);
}
/*
char	**ft_addstr(char **path, int number_path, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char*) * (number_path + 1))))
		return (NULL);
	while (number_path > i)
	{
		tmp[i] = ft_strdup(path[i]);
		i++;
	}
	tmp[number_path] = ft_strdup(str);
	i = number_path + 1;
	tmp[i] = NULL;
	clean_mem(number_path, NULL, path);
	return (tmp);
}*/

int			ft_searchname(char *word, t_com * comm)
{
	int		i;
	char	*tmp;

	i = 0;
	while (word[i] != '=')
		i++;
	tmp = ft_strndup(word, i);
	return (ft_searchpath(comm, tmp));
}

void		ft_export(t_com *comm)
{
	int i;
	int j;
	int flag;

	i = 1;
	j = 0;
	flag = 0;
	if (comm->number_words > i)
	{
		while (comm->number_words > i)
		{
			flag = ft_searchname(comm->words[i], comm);
			if (flag == -1)
			{
				j = 0;
				flag = 0;
				while (comm->words[i][j] != '\0')
				{
					if (comm->words[i][0] == '=')
					{
						write(1, "minishell: export: '", 20);
						write(1, comm->words[i], ft_strlen(comm->words[i]));
						write(1, "': not a valid identifier\n", 26);
						exit_ret = -1;
						break ;
					}
					else if (comm->words[i][j] == '=')
						flag++;
					j++;
				}
				if (flag != 0)
				{
					ft_addstr(comm->path, comm->words[i]);
				//	comm->number_path++;
				}
			}
			else
			{
				free(comm->path[flag]);
				comm->path[flag] = ft_strdup(comm->words[i]);
			}
			i++;
		}
	}
	else
		ft_putquote(comm->path, ft_doublestrlen(comm->path));
	if (exit_ret == -1)
		exit_ret = 1;
	else
		exit_ret = 0;
}