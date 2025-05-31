/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:42:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 19:13:14 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	try_one_command(char *cmd, char **argv, char **envp)
{
	pid_t	my_pid;
	int		error_code;

	error_code = 0;
	my_pid = fork();
	if (my_pid == 0)
	{
		execve(cmd, argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(&error_code);
	return (error_code);
}

//int	try_all_options()
