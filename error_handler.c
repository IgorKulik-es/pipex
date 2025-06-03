/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 20:23:07 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clean_pipex(t_pipe_d *pipex);

int	except_clean(char *name, t_pipe_d *pipex)
{
	if (errno)
	{
		perror(name);
		clean_pipex(pipex);
		exit(errno);
	}
	else if (name)
	{
		write(2, "c function failure: ", 20);
		write(2, name, ft_strlen(name));
		write(2, "\n", 1);
		clean_pipex(pipex);
		exit (EXIT_FAILURE);
	}
	clean_pipex(pipex);
	exit (EXIT_SUCCESS);
}

static void	clean_pipex(t_pipe_d *pipex)
{
	int	index;

	index = 0;
	clean_split(pipex->cmd);
	clean_split(pipex->paths);
	if (pipex->num_args)
		free(pipex->num_args);
	while (pipex->args != NULL && pipex->args[index] != NULL)
	{
		clean_split(pipex->args[index]);
		index++;
	}
	if (pipex->args)
		free(pipex->args);
	if (pipex->fd[0] >= 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] >= 0)
		close(pipex->fd[1]);
	if (pipex->fd_inout[0] >= 0)
		close(pipex->fd_inout[0]);
	if (pipex->fd_inout[1] >= 0)
		close(pipex->fd_inout[1]);
}
