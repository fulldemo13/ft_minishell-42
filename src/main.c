/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:08:29 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/01 18:36:18 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_com *comm)
{
	int		status;
	char	*line;
	int 	i;

	status = -2;
	while (status == -2)
	{
		write(1, "\x1b[32mminishell\\> \x1b[0m", 22);
		line = NULL;
		get_next_line(&line);
		if(!ft_check_syntax(line))
		{	
			comm->commands = ft_split(line, ';');					//take commands
			
			i = 0;
			while (comm->commands[i] && status == -2)				//run commands 1 by 1
			{
				if (!(comm->words = (char **)malloc(sizeof(char *) * (ft_divisor(comm->commands[i]) + 1))))
						exit(status);
				ft_malloc_words(comm->commands[i], comm->words);
				ft_fill_words(comm->commands[i], comm->words);

				check_quotes(comm);
			
				status = compare(comm);
				clean_mem2(comm->words);
				i++;
			}
			clean_mem2(comm->commands);
		}
		free(line);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_com	*comm;
	int		status;

	if (!(comm = (t_com *)malloc(sizeof(t_com))))
		return(0);
	comm = ft_comm_initialize(argc, argv, env, comm);
//	signal (SIGINT, SIG_IGN); //(Ctrl + C)
//	if (!(g_pid = fork()))
//	{
		launch(comm);
//		exit(WEXITSTATUS(status));
//	}
//	while ((wpid = wait(&status)) > 0)
//		NULL;
	clean_mem2(comm->path);
	clean_mem2(comm->bin_path);
	if (comm)
		free(comm);

	system("leaks -q minishell");
	
	return (WEXITSTATUS(status));
}