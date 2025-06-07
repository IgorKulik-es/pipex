/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:12:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/07 15:05:56 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clean_pipex(t_pipe_d *pipex);
static void	print_error(char *s1, char *s2, t_pipe_d *pipex, int err_code);

int	except_clean(char *name, t_pipe_d *pipex, int err_code)
{
	if (2 <= err_code && err_code <= 8)
	{
		print_error("c function failure: ", name, pipex, err_code);
		clean_pipex(pipex);
		exit(1);
	}
	if (err_code == FILE_NF)
		print_error("pipex: no such file or directory: ",
			name, pipex, err_code);
	if ((err_code & FILE_PRM) || err_code == CMD_PERM || err_code == CMD_PERM_L)
		print_error("pipex: permission denied: ", name, pipex, err_code);
	if (err_code == CMD_NF || err_code == CMD_NF_L)
		print_error("pipex: command not found: ", name, pipex, err_code);
	if (err_code == CMD_NF_L || err_code == CMD_PERM_L)
		pipex->to_return = err_code;
	else if ((err_code & FILE_PRM_L))
		pipex->to_return = EXIT_FAILURE;
	else if (err_code == EXIT_FAILURE && pipex->to_return == 0)
		pipex->to_return = EXIT_FAILURE;
	if (err_code == 0)
		clean_pipex(pipex);
	return (0);
}

static void	print_error(char *s1, char *s2, t_pipe_d *pipex, int err_code)
{
	pipex->error = err_code;
	if (s1 == NULL || s2 == NULL)
		return ;
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
}

static void	clean_pipex(t_pipe_d *pipex)
{
	int	index;

	index = -1;
	clean_split(pipex->cmd);
	clean_split(pipex->paths);
	if (pipex->pids)
		free(pipex->pids);
	while (pipex->args != NULL && pipex->args[++index] != NULL)
		clean_split(pipex->args[index]);
	index = -1;
	while (++index < pipex->num_cmd - 1)
		if (pipex->fd[index] > 0)
			close (pipex->fd[index]);
	if (pipex->fd)
		free(pipex->fd);
	if (pipex->args)
		free(pipex->args);
	if (pipex->fd_inout[0] >= 0)
		close(pipex->fd_inout[0]);
	if (pipex->fd_inout[1] >= 0)
		close(pipex->fd_inout[1]);
}
