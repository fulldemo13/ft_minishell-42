/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:43:39 by fulldemo          #+#    #+#             */
/*   Updated: 2020/11/28 18:25:05 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// llegan al afuncion un puntero doble con 6 strings
// leer todos los strings hasta encontrar redireccion (parse error cuando hay demasiadas juntas)
// guardar esos string en un nuevo puntero doble y crear hijo que los ejecute
// funcion que ejecute lo que le pasa como hijo

char **ft_to_execute(t_com *comm, int i, int j)
{
	char **tmp;
	int k;
	int m;

//	printf("{i:%d | j: %d | len:%d}\n", i, j, ft_doublestrlen(comm->words));
	k = 0;
	m = i - j;
	if (!(tmp = (char **)malloc(sizeof(char *) * (m + 1))))
		return NULL;
	while (k < m)
	{	
		tmp[k] = ft_strdup(comm->words[j]);
		j++;
		k++;
	}
	tmp[k] = NULL;

	ft_showdouble(tmp);

	return (tmp);
}


void ft_exec_stdout(t_com *comm, int i, int j)	//Hijo que escribe en el STDOUT
{
	char **tmp;
	pid_t	pod;
	int	res;
	int status;
	char *aux;
	
	printf("{EXEC STDOUT}\n");
	tmp = ft_to_execute(comm, i, j);

	clean_mem2(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);
	
	if (!(pod = fork()))
	{
		if (comm->pipe)
		{
			dup2(comm->fd[0], STDIN_FILENO);
			close(comm->fd[0]);
			close(comm->fd[1]);
		}
		i = 0;
		if ((res = execve(tmp[0], tmp, comm->path)) == -1)
		{
			aux = ft_strjoin(comm->bin_path[i], tmp[0]);
			while ((res = execve(aux, tmp, comm->path) == -1) )
			{
				i++;
				free(aux);
				aux = ft_strjoin(comm->bin_path[i], tmp[0]);
			}
			free(aux);
		}
	}
//	if (!(WIFEXITED(status)))  //No ha ejecutado nada
//		ft_notfound(comm);
	if (comm->pipe)
	{
		close(comm->fd[0]);
		close(comm->fd[1]);
		comm->pipe = 0;
	}
	clean_mem2(tmp);
	wait(&status);
}

void ft_exec_pipe(t_com *comm, int i, int j)		//funciona super guai
{
	char **tmp;
	pid_t pod;
	int res;
	int status;
	char *aux;

	printf("{EXEC PIPE}\n");
	tmp = ft_to_execute(comm, i, j);
	
	clean_mem2(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);

	if (!comm->pipe)
		pipe(comm->fd);
	
	if (!(pod = fork()))
	{
		dup2(comm->fd[1], STDOUT_FILENO);
		close(comm->fd[0]);
		close(comm->fd[1]);
		
		i = 0;
		if ((res = execve(tmp[0], tmp, comm->path)) == -1)
		{
			aux = ft_strjoin(comm->bin_path[i], tmp[0]);
			while ((res = execve(aux, tmp, comm->path) == -1) )
			{
				i++;
				free(aux);
				aux = ft_strjoin(comm->bin_path[i], tmp[0]);
			}
			free(aux);
		}
	}
//	if (!(WIFEXITED(status)))  //No ha ejecutado nada
//		ft_notfound(comm);
		
	clean_mem2(tmp);
	comm->pipe = 1;
	ft_bin_path(comm, i + 1, i + 1);
	wait(&status);
}

void	ft_bin_path(t_com *comm, int i, int j)
{
	//4 tipos de redirecciones "<" ">" ">>" "|"
	//create tmp
	
	while (i < ft_doublestrlen(comm->words))
	{
		if (!ft_strcmp(comm->words[i], "|"))
		{
			ft_exec_pipe(comm, i, j);
			return;
		}
		i++;
	}
	if (i == ft_doublestrlen(comm->words))
		ft_exec_stdout(comm, i, j);
	//puedo enviar a que cree un hijo con las caracteristicas de |
	
}
/*
int	main()
{
	// ls -l | wc > file.txt
	// | crea un nuevo hijo con un dup para pasar el resultado de uno a otro
	// redirecciones no crean hijos sino que escriben en el archivo (get_fd)
	int fd1[2];
	int fd2;
	int status;
	int pid;
	int read_end = 0;
	int write_end = 1;
	//encontramos un | creamos hijo con pipe
	pipe(fd1);
	pid = fork();
	if (pid == 0) //hijo nacido del | con todo abierto por el pipe()
	{
		 close(fd1[read_end]);
		 dup2(fd1[write_end], STDOUT_FILENO);
		 close(fd1[write_end]);
		 //ejecutamos comando (ls -l)
		 execlp("/bin/ls", "ls", "-l", NULL);
	}
	else	//el padre que ejecuta el siguiente comando en otro hijo
	{
		close(fd1[write_end]); //al cerrar el extremo de excritura el hijo hereda el extremo de lecetura que es el resultado del comado anterior
		
		pid = fork();
		if (pid == 0) //hijo 2 nacido por el >
		{
			fd2 = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC);
			dup2(fd1[read_end], STDIN_FILENO);	//cambia la lectura del input al extrmo del pipe
			close(fd1[read_end]);

			dup2(fd2, STDOUT_FILENO);	//cambia la escritura del stdout al file descriptor del archivo

			//ejecutar comando (wc)
			execlp("/usr/bin/wc", "wc", NULL);
		}
		else
		{
			close(fd1[read_end]);	//cerramos el otro extremo
		}
	}
	//un wait para cada hijo
	wait(&status);
	wait(&status);

	return(0);
}*/