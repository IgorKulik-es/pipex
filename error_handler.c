/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/04 16:56:16 by ikulik           ###   ########.fr       */
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
		write(2, name, ft_strlen(name));
		write(2, ": c function failure\n", 21);
		clean_pipex(pipex);
		exit (EXIT_FAILURE);
	}
	clean_pipex(pipex);
	exit (EXIT_SUCCESS);
}

int	except_clean1(char *name, t_pipe_d *pipex, int err_code)
{
	if (1 <= err_code && err_code <= 6)
	{
		print_error("c function failure: ", name, pipex, err_code);
		clean_pipex(pipex);
		exit(1);
	}
	if (err_code == FILE_NF || err_code == FILE_NF_L)
		print_error("pipex: no such file or directory: ",
			name, pipex, err_code);
	if (err_code == FILE_PRMT || err_code == CMD_PERM || err_code == CMD_PERM_L)
		print_error("pipex: permission denied: ", name, pipex, err_code);
	if (err_code == CMD_NF || err_code == CMD_NF_L)
		print_error("pipex: command not found: ", name, pipex, err_code);
}

void	print_error(char *s1, char *s2, t_pipe_d *pipex, int err_code)
{
	if (s1 == NULL || s2 == NULL)
		return ;
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	pipex->error |= err_code;
}

static void	clean_pipex(t_pipe_d *pipex)
{
	int	index;

	index = -1;
	clean_split(pipex->cmd);
	clean_split(pipex->paths);
	if (pipex->num_args)
		free(pipex->num_args);
	while (pipex->args != NULL && pipex->args[++index] != NULL)
		clean_split(pipex->args[index]);
	if (pipex->args)
		free(pipex->args);
	if (pipex->fd >= 0)
		close(pipex->fd);
	if (pipex->fd_inout[0] >= 0)
		close(pipex->fd_inout[0]);
	if (pipex->fd_inout[1] >= 0)
		close(pipex->fd_inout[1]);
	if (pipex->stdio[0] >= 0)
		close(pipex->stdio[0]);
	if (pipex->stdio[1] >= 0)
		close(pipex->stdio[1]);
}
