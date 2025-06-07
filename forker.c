/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:42:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/07 17:18:41 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	last_command_child(t_pipe_d *pipex, int *fd);

void	run_first_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		fd[2];

	if (pipe(fd) == -1)
		except_clean("pipe", pipex, PIPE);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex, FORK);
	if (my_pid == 0)
	{
		close(fd[0]);
		if ((dup2(pipex->fd_inout[0], 0) == -1 || dup2(fd[1], 1) == -1)
			&& pipex->fd_inout[0] != -1)
			except_clean("dup2", pipex, DUP2);
		if (pipex->fd_inout[0] != -1)
			execve(pipex->cmd[0], pipex->args[0], pipex->envp);
		except_clean(NULL, pipex, 0);
		exit (1);
	}
	else
		pipex->pids[0] = my_pid;
	close(fd[1]);
	pipex->fd[0] = fd[0];
}

void	run_last_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		fd[2];

	if (pipe(fd) == -1)
		except_clean("pipe", pipex, PIPE);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex, FORK);
	if (my_pid == 0)
		last_command_child(pipex, fd);
	else
		pipex->pids[pipex->num_cmd - 1] = my_pid;
	close(fd[1]);
}

static void	last_command_child(t_pipe_d *pipex, int *fd)
{
	close(fd[0]);
	if ((dup2(pipex->fd[pipex->num_cmd - 2], 0) == -1
			|| dup2(pipex->fd_inout[1], 1) == -1) && pipex->fd_inout[1] != -1)
		except_clean("dup2", pipex, DUP2);
	if (pipex->fd_inout[1] != -1)
		execve(pipex->cmd[pipex->num_cmd - 1],
			pipex->args[pipex->num_cmd - 1], pipex->envp);
	except_clean(NULL, pipex, 0);
	exit (1);
}

void	main_waiter(t_pipe_d *pipex)
{
	int	error_code;
	int	error_dummy;
	int	cmd_index;

	error_code = 0;
	error_dummy = 0;
	cmd_index = pipex->num_cmd - 2;
	waitpid(pipex->pids[pipex->num_cmd - 1], &error_code, 0);
	close(pipex->fd[pipex->num_cmd - 2]);
	while (cmd_index > 0)
	{
		waitpid(pipex->pids[cmd_index], &error_dummy, 0);
		close(pipex->fd[cmd_index - 1]);
		cmd_index--;
	}
	waitpid(pipex->pids[0], &error_dummy, 0);
	wait(&error_dummy);
	if (error_code > 0)
		except_clean(pipex->cmd[pipex->num_cmd - 1], pipex, EXIT_FAILURE);
}
