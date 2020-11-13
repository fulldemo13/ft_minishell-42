/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:17:10 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/13 17:32:57 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int		is_redirection(char c)
{	
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	return (0);
}

void	clean_mem2(char **commands)
{
	int i;

	i = 0;
	while (commands[i] != NULL)
	{
		free(commands[i]);
		//commands[i][0] = '\0';
		i++;
	}
	free(commands);
	//commands = NULL; 
}

void	clean_mem(int len, char *line, char **commands)
{
	len--;
	if (commands)
	{
			while (len >= 0)
			{
				free(commands[len]);
				len--;
			}
			free(commands);
			commands = NULL;
	}
	if (line)
		free(line);
}

void	ft_putstr(char **str)
{
	int	i;
	
	i = 0;
	while (str[i] != NULL)
	{
		write(global_fd, str[i], ft_strlen(str[i]));
		write(global_fd, "\n", 1);
		i++;
	}
}

t_com	*ft_comm_initialize(int argc, char **argv, char ** env, t_com *comm)
{
	(void)argc;
	(void)argv;
//	comm->number_com = 0;
//	comm->number_path = ft_doublestrlen(env);
	comm->path = ft_doublestrdup(env);
	comm->bin_path = ft_getbinpath(comm);
	exit_ret = 0;
	return (comm);
}

int		ft_searchpath(t_com *comm, char *words)
{
	int	i;
	int	j;

	i = 0;
	while (comm->path[i] != NULL)
	{
		j = 0;
		while (comm->path[i][j] != '\0')
		{
			if (comm->path[i][j] == '=' && words[j] == '\0')
				return(i);
			else if (comm->path[i][j] != words[j])
				break ;
			j++;
		}
		i++;
	}
	return (-1);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	if (len > ft_strlen(s2))
		len = ft_strlen(s2);
	if (!(src = malloc(sizeof(char) * (ft_strlen(s1) + len + 1))))
		return (NULL);
	while (s1[i])
	{
		src[i] = s1[i];
		i++;
	}
	while (len > 0)
	{
		src[i] = s2[j];
		j++;
		i++;
		len--;
	}
	src[i] = '\0';
	return (src);
}

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	i;
	char	*r;

	i = 0;
	while (s1[i] != '\0' && i < len)
		i++;
	r = malloc(i + 1);
	if (r == NULL)
	{
		return (0);
	}
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

void	ft_showdouble(char **str)
{
	int i = 0;
	while (str[i] != NULL)
	{
		printf("[%s]\n", str[i]);
		i++;
	}
	printf("[END]\n");
}