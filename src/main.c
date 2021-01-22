/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:08:29 by fulldemo          #+#    #+#             */
/*   Updated: 2021/01/22 10:38:29 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sighandler()
{
	write(1, "\033[2D\033[0K", 9);
	write(1, "\n", 1);
	write(1, "\x1b[32mminishell\\>\x1b[0m", 21);
}

int		launch(t_com *comm)
{
	int		status;
	char	*line;
	int 	i;

	status = -2;
	while (status == -2)
	{
		write(1, "\x1b[32mminishell\\>\x1b[0m", 21);
		line = NULL;
		signal (SIGINT, sighandler); 			//Ctrl + C
		if (!get_next_line(&line))				//Ctrl + D
			status = ft_exit(comm);
		if(!ft_check_syntax(line) && status == -2)
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
				
				ft_clean_mem(comm->words);
				i++;
			}
			ft_clean_mem(comm->commands);
		}
		free(line);

		printf("Exit_ret:%d\n", exit_ret);
	}
	return (status);
}

int		main(int argc, char **argv, char **env)
{
	t_com	*comm;
	int		status;

	if (!(comm = (t_com *)malloc(sizeof(t_com))))
		return(0);
	comm = ft_comm_initialize(argc, argv, env, comm);
	status = launch(comm);
	ft_clean_mem(comm->path);
	ft_clean_mem(comm->bin_path);
	free(comm);

	system("leaks -q minishell");
	
	return (status);
}