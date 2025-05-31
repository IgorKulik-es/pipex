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


char	**create_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	**result;
	int		size_env;
	int		index;

	paths = parse_path(envp);
	index = 0;
	if (paths == NULL)
		return ((char **)clean_split(paths));
	size_env = measure_array(paths);
	result = (char **)malloc((size_env + 1) * sizeof(char *));
	if (result == NULL)
		return ((char **)clean_split(paths));
	while (index < size_env)
	{
		result[index] = ft_strjoin(paths[index], "/", cmd);
		if (result == NULL)
			return (clean_split(paths), (char **)clean_split(result));
		index++;
	}
	result[index] = NULL;
	clean_split(paths);
	return (result);
}

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
