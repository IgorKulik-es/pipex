/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:42:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 19:43:30 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	last_command_child(t_pipe_d *pipex, int *fd);

void	run_middle_command(int index_cmd, t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	if (pipe(fd) == -1)
		except_clean("pipe", pipex, PIPE);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex, FORK);
	if (my_pid == 0)
	{
		close(fd[0]);
		if ((dup2(pipex->fd, 0) == -1 || dup2(fd[1], 1) == -1))
			except_clean("dup2", pipex, DUP2);
		execve(pipex->cmd[index_cmd], pipex->args[index_cmd], pipex->envp);
		except_clean(NULL, pipex, 0);
		exit (1);
	}
	else
		waitpid(my_pid, &error_code, 0);
	close(fd[1]);
	pipex->fd = fd[0];
}

void	run_first_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
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
		waitpid(my_pid, &error_code, 0);
	close(fd[1]);
	pipex->fd = fd[0];
}

void	run_last_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	if (pipe(fd) == -1)
		except_clean("pipe", pipex, PIPE);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex, FORK);
	if (my_pid == 0)
		last_command_child(pipex, fd);
	else
		waitpid(my_pid, &error_code, 0);
	close(fd[1]);
	close(fd[0]);
	if (error_code > 0)
		except_clean(pipex->cmd[pipex->num_cmd - 1], pipex, EXIT_FAILURE);
}

static void	last_command_child(t_pipe_d *pipex, int *fd)
{
	close(fd[0]);
	if ((dup2(pipex->fd, 0) == -1 || dup2(pipex->fd_inout[1], 1) == -1)
		&& pipex->fd_inout[1] != -1)
		except_clean("dup2", pipex, DUP2);
	if (pipex->fd_inout[1] != -1)
		execve(pipex->cmd[pipex->num_cmd - 1],
			pipex->args[pipex->num_cmd - 1], pipex->envp);
	except_clean(NULL, pipex, 0);
	exit (1);
}
