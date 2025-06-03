/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:42:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 16:24:54 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	run_one_command(int index_cmd, t_pipe_d *pipex)
{
	pid_t	my_pid;
	int		error_code;
	int		fd[2];

	error_code = 0;
	my_pid = fork();
	if (my_pid == 0)
	{
		execve(pipex->cmd[index_cmd], pipex->args[index_cmd], pipex->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(&error_code);
	if (error_code > 0)
		except_clean(pipex->cmd[index_cmd], pipex);
	return (error_code);
}
