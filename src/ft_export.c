/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 09:53:31 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 10:06:18 by fulldemo         ###   ########.fr       */
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

//hijo solamente muestra cuando export esta solo
void		ft_export_child(t_com *comm, char **tmp)
{	
	if (ft_doublestrlen(tmp) == 1)
		ft_putquote(comm->path, ft_doublestrlen(comm->path));
	exit(0);
}


void		ft_export_parent(t_com *comm, char **tmp) //tmp es la linea guay de comando
{
	int i;
	int j;
	int flag;
	char **aux;

	i = 1;
	j = 0;
	flag = 0;
	
	while (tmp[i] != NULL)
	{
		flag = ft_searchname(tmp[i], comm);
		if (flag == -1)
		{
			j = 0;
			flag = 0;
			while (tmp[i][j] != '\0')
			{
				if (tmp[i][0] == '=')
				{
					write(1, "minishell: export: '", 20);
					write(1, tmp[i], ft_strlen(tmp[i]));
					write(1, "': not a valid identifier\n", 26);
					break ;
				}
				else if (tmp[i][j] == '=')
					flag++;
				j++;
			}
			if (flag != 0)
			{
				aux = ft_addstr(comm->path, comm->words[i]);
				clean_mem2(comm->path);
				comm->path = aux;
			}
		}
		else
		{
			free(comm->path[flag]);
			comm->path[flag] = ft_strdup(tmp[i]);
		}
		i++;
	}
}