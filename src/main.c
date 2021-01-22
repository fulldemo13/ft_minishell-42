/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:08:29 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/22 17:24:11 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	DESCOMENTAR MAKEFILE PARA EL LIBFT
*/

#include "minishell.h"

void	ft_sighandler(int i)
{
	i = 0;
	write(1, "\033[2D\033[0K", 9);
	write(1, "\n", 1);
	write(1, "\x1b[32mminishell\\>\x1b[0m", 21);
}

int		ft_run_commands(t_com *comm, int status)
{
	int		i;

	i = 0;
	while (comm->commands[i] && status == -1)
	{
		if (!(comm->words = (char **)malloc(sizeof(char *) *
		(ft_divisor(comm->commands[i]) + 1))))
			exit(status);
		if (ft_malloc_words(comm->commands[i], comm->words))
			return (1);
		ft_fill_words(comm->commands[i], comm->words);
		check_quotes(comm);
		status = compare(comm);
		ft_clean_mem(comm->words);
		i++;
	}
	return (status);
}

int		ft_launch(t_com *comm)
{
	int		status;
	char	*line;

	status = -1;
	while (status == -1)
	{
		write(1, "\x1b[32mminishell\\>\x1b[0m", 21);
		line = NULL;
		signal(SIGINT, ft_sighandler);
		if (!get_next_line(&line))
			status = ft_sig_exit();
		if (!ft_check_syntax(line) && status == -1)
		{
			comm->commands = ft_split(line, ';');
			status = ft_run_commands(comm, status);
			ft_clean_mem(comm->commands);
		}
		free(line);
	}
	return (status);
}

int		main(int argc, char **argv, char **env)
{
	t_com	*comm;
	int		status;

	if (!(comm = (t_com *)malloc(sizeof(t_com))))
		return (0);
	comm = ft_comm_initialize(argc, argv, env, comm);
	status = ft_launch(comm);
	ft_clean_mem(comm->path);
	ft_clean_mem(comm->bin_path);
	free(comm);

	system("leaks -q minishell");

	return (status);
}