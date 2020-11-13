/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:08:29 by fulldemo          #+#    #+#             */
/*   Updated: 2020/06/30 19:39:26 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_com *comm)
{
	int		status;
	int		number;
	char	*line;
	int 	i;
	char	**tmp;

	status = -2;
	while (status == -2)
	{
		global_fd = 1;
		write(1, "\x1b[32mminishell\\> \x1b[0m", 22);
		line = NULL;
		get_next_line(&line);
		if(!ft_quotes(line))
		{
			write(1, "minishell: syntax error multiline\n", 34);
			exit_ret = 128;
			free(line);
		}
		else if((number = ft_semicolon(line)) == -1)
		{
			write(1, "minishell: syntax error near unexpected token ';'\n", 50);
			exit_ret = 128;
			free(line);
		}
		else
		{	
			comm->commands = ft_split(line, ';');
			comm->number_com = ft_doublestrlen(comm->commands);
//	printf("----->comandos:%d\n", comm->number_com);
			
			i = 0;
			while (comm->number_com > i && status == -2)
			{
				comm->number_words = divider(comm->commands[i]);
				number = comm->number_words;
//	printf("----->words:%d\n", comm->number_words);
				comm->words = get_commands(comm->commands[i]);
				tmp = parse_redirection(comm);
				clean_mem(number, NULL, comm->words);
				comm->words = tmp;
				check_quotes(comm);
				
//	printf("----->[%s]\n", comm->words[0]);
/////////////Printear commands////////////////////
/*
				number = 0;
				while (comm->number_words > number)
				{
					printf("[%s]\n", comm->words[number]);
					number++;
				}
*/
/////////////////////////////////////////////////


				get_fd(comm);
				status = compare(comm);
				if (comm->number_words > 0)
					clean_mem(comm->number_words, NULL, comm->words);
				if (global_fd != 1)
					close(global_fd);	
				i++;
			}
			if (comm->number_com > 0)
				clean_mem(comm->number_com, line, comm->commands);
		}
	}
	if (status == -1)
		status = 0;
	exit(status);
}

int		main(int argc, char **argv, char **env)
{
	t_com	*comm;
	pid_t	wpid;
	int		status;

	if (!(comm = (t_com *)malloc(sizeof(t_com))))
		return(0);
	comm = ft_comm_initialize(argc, argv, env, comm);
	signal (SIGINT, SIG_IGN); //(Ctrl + C)
	if (!(g_pid = fork()))
	{
		launch(comm);
		exit(WEXITSTATUS(status));
	}
	while ((wpid = wait(&status)) > 0)
		NULL;
	clean_mem(comm->number_path, NULL, comm->path);
	clean_mem(comm->number_bin_path, NULL, comm->bin_path);
	free(comm);

//	system("leaks minishell");
	
	return (WEXITSTATUS(status));
}