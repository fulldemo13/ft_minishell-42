/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:53:31 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/27 10:43:38 by fulldemo         ###   ########.fr       */
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
		write(1, "declare -x ", 11);
		i = 0;
		while (str[j][i] != '\0')
		{
			flag = 0;
			write(1, &str[j][i], 1);
			if (str[j][i] == '=' && !flag)
			{
				write(1, "\"", 2);
				flag++;
			}
			i++;
		}
		j++;
		write(1, "\"\n", 2);
	}
}

int		ft_searchname(char *word, t_com *comm)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_strchr(word, '='))
		return (-1);
	while (word[i] != '=')
		i++;
	tmp = ft_strndup(word, i);
	i = ft_searchpath(comm, tmp);
	free(tmp);
	return (i);
}

void	ft_export_child(t_com *comm, char **tmp, int *fd)
{
	if (ft_doublestrlen(tmp) == 1)
		ft_putquote(comm->path, ft_doublestrlen(comm->path));
	g_exit_ret = 0;
	if (fd)
	{
		close(fd[0]);
		write(fd[1], &g_exit_ret, sizeof(int));
		close(fd[1]);
	}
	exit(0);
}

int		ft_export_equal(char *tmp)
{
	if (!ft_strchr(tmp, '='))
	{
		write(1, "minishell: export: '", 20);
		write(1, tmp, ft_strlen(tmp));
		write(1, "': not a valid identifier\n", 26);
		g_exit_ret = 1;
		return (1);
	}
	return (0);
}

void	ft_export_parent(t_com *comm, char **tmp)
{
	int i;
	int flag;

	i = 1;
	while (tmp[i] != NULL)
	{
		flag = ft_searchname(tmp[i], comm);
		if (flag == -1)
		{
			flag = 0;
			if (!ft_export_equal(tmp[i]))
				flag++;
			if (flag != 0)
				ft_addstr(comm, tmp[i]);
		}
		else
		{
			free(comm->path[flag]);
			comm->path[flag] = ft_strdup(tmp[i]);
		}
		i++;
	}
}
