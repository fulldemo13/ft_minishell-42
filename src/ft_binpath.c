/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:43:39 by fulldemo          #+#    #+#             */
/*   Updated: 2020/12/21 09:51:42 by fulldemo         ###   ########.fr       */
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

	k = 0;
	m = i - j;
	if (!(tmp = (char **)malloc(sizeof(char *) * (m + 1))))
		return (NULL);
	while (k < m)
	{	
		tmp[k] = ft_strdup(comm->words[j]);
		j++;
		k++;
	}
	tmp[k] = NULL;
	
//	ft_showdouble(tmp);

	return (tmp);
}

void ft_exec_comm(t_com *comm, char **tmp)
{
	int		i;
	char	*aux;
	int		res;

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


void ft_searchexec(t_com * comm, char **tmp)
{
	if (!ft_strcmp(tmp[0], "echo"))
		ft_echo(tmp);
	else if (!ft_strcmp(tmp[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(tmp[0], "env"))
		ft_env(comm, tmp);
	else if (!ft_strcmp(tmp[0], "export"))
		ft_export_child(comm, tmp);
	else
		ft_exec_comm(comm, tmp);
}



void ft_read_fd(t_com *comm, int i, int j) //lee del archivo <
{
	char **tmp;
	pid_t	pod;
	int		status;
	int		fd;

	//printf("{EXEC READ FD}\n");

	if ((fd = open(comm->words[i + 1], O_RDONLY)) == -1)
	{
		ft_notfound(comm->words[i + 1]);
		return ;
	}
	
	tmp = ft_to_execute(comm, i, j);
	ft_clean_mem(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);

	if (comm->pipe >= 1)		//Cierra pipes
	{
		close(comm->fd[comm->pipe - 1][0]);
		close(comm->fd[comm->pipe - 1][1]);
	}

	if (!(pod = fork()))
	{	
		dup2(fd, STDIN_FILENO);	//le decimos que la entrada sea el archivo
		if (comm->pipe != -1)
		{
			dup2(comm->fd[comm->pipe][1], STDOUT_FILENO);
			close(comm->fd[comm->pipe][0]);
			close(comm->fd[comm->pipe][1]);
		}
		
		ft_searchexec(comm, tmp);
	}
	wait(&status);
	if (comm->pipe != -1)
	{
		close(comm->fd[comm->pipe][0]);
		close(comm->fd[comm->pipe][1]);
	}
	comm->pipe = -1;
	close(fd);

	ft_clean_mem(tmp);
}

void ft_write_fd(t_com *comm, int i, int j)	//Hijo que escribe en nuevo archivo > y >>
{
	//j es la posición siguiente a la última redireccíon
	//i es la posicion de la redirección actual
	char	**tmp;
	pid_t	pod;
	int		status;
	int		fd;
	
	//printf("{EXEC WRITE FD}\n");

	fd = -1;
	tmp = ft_to_execute(comm, i, j);

	ft_clean_mem(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);

	while (comm->words[i + 1] != NULL)			//Abre multiples archivos
	{	
		if (!ft_strcmp(comm->words[i], ">"))
		{
			if (fd != -1)
				close(fd);
			if ((fd = open(comm->words[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
				ft_notfound(comm->words[i + 1]);
		}
		if (!ft_strcmp(comm->words[i], ">>"))
		{
			if (fd != -1)
				close(fd);
			if ((fd = open(comm->words[i + 1], O_WRONLY | O_CREAT | O_APPEND , 0777)) == -1)
				ft_notfound(comm->words[i + 1]);
		}
		i++;
	}

	if (comm->pipe >= 1)		//Cierra pipes
	{
		close(comm->fd[comm->pipe - 1][0]);
		close(comm->fd[comm->pipe - 1][1]);
	}

	if (!(pod = fork()))
	{
		
		dup2(fd, STDOUT_FILENO);	//le decimos que el OUT lo escriva en el archivo
		if (comm->pipe != -1)
		{
			dup2(comm->fd[comm->pipe][0], STDIN_FILENO);
			close(comm->fd[comm->pipe][0]);
			close(comm->fd[comm->pipe][1]);
		}
		
		ft_searchexec(comm, tmp);
	}
	wait(&status);
	if (comm->pipe != -1)
	{
		close(comm->fd[comm->pipe][0]);
		close(comm->fd[comm->pipe][1]);
	}
	comm->pipe = -1;
	close(fd);
	ft_clean_mem(tmp);
}

void ft_exec_stdout(t_com *comm, int i, int j)	//Hijo que escribe en el STDOUT
{
	char	**tmp;
	pid_t	pod;
	int		status;
	
	//printf("{EXEC STDOUT}\n");

	tmp = ft_to_execute(comm, i, j);
	ft_clean_mem(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);

	if (comm->pipe >= 1)		//Cierra pipes
	{
		close(comm->fd[comm->pipe - 1][0]);
		close(comm->fd[comm->pipe - 1][1]);
	}

	if (!(pod = fork()))
	{
		if (comm->pipe != -1)
		{
			dup2(comm->fd[comm->pipe][0], STDIN_FILENO);
			close(comm->fd[comm->pipe][0]);
			close(comm->fd[comm->pipe][1]);
		}
		ft_searchexec(comm, tmp);
	}

	wait(&status);

	if (!(WIFEXITED(status) && (WEXITSTATUS(status) == 0)))
		ft_notfound(tmp[0]);
	
	if (!ft_strcmp(tmp[0], "export"))
	{
		ft_export_parent(comm, tmp);
	}
		
	if (comm->pipe != -1)
	{
		close(comm->fd[comm->pipe][0]);
		close(comm->fd[comm->pipe][1]);
	}
	comm->pipe = -1;
	ft_clean_mem(tmp);
}

void ft_exec_pipe(t_com *comm, int i, int j)
{
	char **tmp;
	pid_t pod;
	int status;

	//printf("{EXEC PIPE}\n");

	tmp = ft_to_execute(comm, i, j);
	ft_clean_mem(comm->bin_path);
	comm->bin_path = ft_getbinpath(comm);

	comm->pipe++;
	pipe(comm->fd[comm->pipe]);

	if (comm->pipe >= 2)		//close pipes
	{
		close(comm->fd[comm->pipe - 2][0]);
		close(comm->fd[comm->pipe - 2][1]);
	}

	if (!(pod = fork()))
	{
		if (comm->pipe == 0)	//First
		{
			close(comm->fd[comm->pipe][0]);
			dup2(comm->fd[comm->pipe][1], STDOUT_FILENO);
			close(comm->fd[comm->pipe][1]);
		}
		else		//Mid
		{
			close(comm->fd[comm->pipe - 1][1]);
			dup2(comm->fd[comm->pipe - 1][0], STDIN_FILENO);
			close(comm->fd[comm->pipe - 1][0]);
			close(comm->fd[comm->pipe][0]);
			dup2(comm->fd[comm->pipe][1], STDOUT_FILENO);
			close(comm->fd[comm->pipe][1]);
		}
		
		ft_searchexec(comm, tmp);
	}
//	if (!(WIFEXITED(status)))  //No ha ejecutado nada
//		ft_notfound(comm);		
	ft_clean_mem(tmp);
	ft_bin_path(comm, i + 1, i + 1);
	wait(&status);		//No TOCAR
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
		if (!ft_strcmp(comm->words[i], ">") || !ft_strcmp(comm->words[i], ">>"))
		{
			ft_write_fd(comm, i, j);
			return;
		}
		if (!ft_strcmp(comm->words[i], "<"))
		{
			ft_read_fd(comm, i, j);
			return;
		}
		i++;
	}
	if (i == ft_doublestrlen(comm->words))
		ft_exec_stdout(comm, i, j);	
}