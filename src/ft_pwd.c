/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:37:54 by fulldemo          #+#    #+#             */
/*   Updated: 2020/03/02 16:50:27 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, -1);
	write(global_fd, buf, ft_strlen(buf));
	write(global_fd, "\n", 1);
	free(buf);
	buf = NULL;
	exit_ret = 0;
}