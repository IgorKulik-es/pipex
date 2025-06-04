/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:42:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/04 13:48:44 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	run_one_command(int index_cmd, t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	if (pipe(fd) == -1)
		except_clean("pipe", pipex);
	printf("Pipes fildes: %d, %d\n", fd[0], fd[1]);
	my_pid = fork();
	if (my_pid == 0)
	{
		close(fd[0]);
		if (dup2(pipex->fd, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
			except_clean("dup2", pipex);
		execve(pipex->cmd[index_cmd], pipex->args[index_cmd], pipex->envp);
		except_clean("execve", pipex);
	}
	else
	{
		waitpid(my_pid, &error_code, 0);
		close(fd[1]);
		pipex->fd = fd[0];
	}
	if (error_code > 0)
		except_clean(pipex->cmd[index_cmd], pipex);
	return (error_code);
}

void	run_first_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	if (pipe(fd) == -1)
		except_clean("pipe", pipex);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex);
	if (my_pid == 0)
	{
		close(fd[0]);
		if (dup2(pipex->fd_inout[0], 0) == -1 || dup2(fd[1], 1) == -1)
			except_clean("dup2", pipex);
		execve(pipex->cmd[0], pipex->args[0], pipex->envp);
		except_clean("execve", pipex);
	}
	else
		waitpid(my_pid, &error_code, 0);
	close(fd[1]);
	pipex->fd = fd[0];
	if (error_code > 0)
		except_clean(pipex->cmd[0], pipex);
}

void	run_last_command(t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	if (pipe(fd) == -1)
		except_clean("pipe", pipex);
	my_pid = fork();
	if (my_pid == -1)
		except_clean("fork", pipex);
	if (my_pid == 0)
	{
		close(fd[0]);
		if (dup2(pipex->fd, 0) == -1 || dup2(pipex->fd_inout[1], 1) == -1)
			except_clean("dup2", pipex);
		execve(pipex->cmd[pipex->num_cmd - 1],
			pipex->args[pipex->num_cmd - 1], pipex->envp);
		except_clean("execve", pipex);
	}
	else
		waitpid(my_pid, &error_code, 0);
	close(fd[1]);
	close(fd[0]);
	if (error_code > 0)
		except_clean(pipex->cmd[0], pipex);
}


