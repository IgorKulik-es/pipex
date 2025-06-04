/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:33:12 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/04 16:56:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_cmd(int cmd_index, int i, char **cmd_paths, t_pipe_d *pipex);

static char	**parse_path(t_pipe_d *pipex)
{
	char	**env_buffer;

	env_buffer = pipex->envp;
	while (*env_buffer)
	{
		if (ft_strncmp("PATH", *env_buffer, 4) == 0)
			break ;
		env_buffer++;
	}
	if (*env_buffer == NULL)
		return (NULL);
	env_buffer = ft_split(*env_buffer, ':', &pipex->path_size);
	if (env_buffer == NULL)
		except_clean("malloc", pipex);
	return (env_buffer);
}

static char	**create_cmd_path(char *cmd, t_pipe_d *pipex)
{
	char	**result;
	int		index;

	index = 0;
	if (pipex->paths == NULL)
		pipex->paths = parse_path(pipex);
	if (pipex->paths == NULL)
		except_clean(cmd, pipex);
	result = (char **)malloc((pipex->path_size + 1) * sizeof(char *));
	if (result == NULL)
		except_clean("malloc", pipex);
	while (pipex->paths[index])
	{
		result[index] = ft_strjoin(pipex->paths[index], "/", cmd);
		if (result[index] == NULL && cmd != NULL)
		{
			clean_split(result);
			except_clean("malloc", pipex);
		}
		index++;
	}
	result[index] = NULL;
	return (result);
}

int	parse_commands(t_pipe_d *pipex)
{
	char	**paths;
	int		index;
	int		access_status;
	int		cmd_index;

	cmd_index = -1;
	while (++cmd_index < pipex->num_cmd)
	{
		index = 0;
		access_status = check_access(pipex->cmd[cmd_index], EXECUTE);
		if (access_status == 0)
			continue ;
		if (access_status == -2)
			except_clean(pipex->cmd[cmd_index], pipex);
		paths = create_cmd_path(pipex->cmd[cmd_index], pipex);
		while (paths[index] && access_status != 0)
		{
			access_status = get_cmd(cmd_index, index, paths, pipex);
			index++;
		}
		clean_split(paths);
		if (access_status != 0)
			except_clean(pipex->cmd[cmd_index], pipex);
	}
	return (0);
}

static int	get_cmd(int cmd_index, int i, char **cmd_paths, t_pipe_d *pipex)
{
	int	access_status;

	access_status = check_access(cmd_paths[i], EXECUTE);
	if (access_status == 0)
	{
		free(pipex->cmd[cmd_index]);
		pipex->cmd[cmd_index] = ft_strjoin(cmd_paths[i], "", "");
		if (pipex->cmd[cmd_index] == NULL)
		{
			clean_split(cmd_paths);
			except_clean("malloc", pipex);
		}
		return (0);
	}
	else if (access_status == -2)
	{
		clean_split(cmd_paths);
		except_clean(cmd_paths[cmd_index], pipex);
	}
	return (access_status);
}

int	check_access(char *cmd, int mode)
{
	int	access_status;

	access_status = access(cmd, F_OK);
	if (access_status == -1)
		return (-1);
	if (mode == READ)
		access_status = access(cmd, R_OK);
	if (mode == EXECUTE)
		access_status = access(cmd, X_OK);
	if (mode == WRITE)
		access_status = access(cmd, W_OK);
	if (access_status == -1)
		return (-2);
	return (0);
}
