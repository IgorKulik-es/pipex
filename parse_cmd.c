/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:33:12 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 17:50:56 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_path(char **envp)
{
	char	**env_buffer;

	env_buffer = envp;
	while (*env_buffer)
	{
		if (ft_strncmp("PATH", *env_buffer, 4) == 0)
			break ;
		env_buffer++;
	}
	if (*env_buffer == NULL)
		return (NULL);
	env_buffer = ft_split(*env_buffer, ':');
	if (env_buffer == NULL)
		return (NULL);
	return (env_buffer);
}

char	**create_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	**result;
	int		size_env;
	int		index;

	paths = parse_path(envp);
	if (paths == NULL)
		return (NULL);
	index = 0;
	size_env = measure_array(paths);
	result = (char **)malloc((size_env + 1) * sizeof(char *));
	if (result == NULL)
		return ((char **)clean_split(paths));
	while (index < size_env)
	{
		result[index] = ft_strjoin(paths[index], "/", cmd);
		if (result[index] == NULL)
			return (clean_split(paths), (char **)clean_split(result));
		index++;
	}
	result[index] = NULL;
	clean_split(paths);
	return (result);
}

char	*find_command(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	int		index;
	int		have_access;

	index = 0;
	result = NULL;
	have_access = access(cmd, X_OK);
	if (have_access == 0)
		return (ft_strjoin(cmd, "", ""));
	paths = create_cmd_path(cmd, envp);
	if (paths == NULL)
	{
		perror("No such file or directory");
		return (NULL);
	}
	while (have_access != 0 && paths[index])
	{
		have_access = access(paths[index], X_OK);
		index++;
	}
	if (have_access == 0)
		result = ft_strjoin(paths[index - 1], "", "");
	clean_split(paths);
	return (result);
}
