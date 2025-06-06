/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:33:12 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 20:25:27 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		except_clean("malloc", pipex, MALLOC);
	return (env_buffer);
}

static char	**create_cmd_path(char *cmd, t_pipe_d *pipex)
{
	char	**result;
	int		index;

	index = 0;
	if (pipex->paths == NULL)
		pipex->paths = parse_path(pipex);
	result = (char **)malloc((pipex->path_size + 1) * sizeof(char *));
	if (result == NULL)
		except_clean("malloc", pipex, MALLOC);
	while (pipex->paths[index])
	{
		result[index] = ft_strjoin(pipex->paths[index], "/", cmd);
		if (result[index] == NULL && cmd != NULL)
		{
			clean_split(result);
			except_clean("malloc", pipex, MALLOC);
		}
		index++;
	}
	result[index] = NULL;
	return (result);
}

int	parse_one_command(t_pipe_d *pipex, int cmd_index)
{
	char	**paths;
	int		index;
	int		access_status;

	index = 0;
	access_status = check_access(pipex->cmd[cmd_index], EXECUTE);
	if (access_status == 0)
		return (0);
	if (access_status == -2)
		return (-2);
	paths = create_cmd_path(pipex->cmd[cmd_index], pipex);
	while (paths[index] && access_status != 0)
	{
		access_status = get_cmd(cmd_index, index, paths, pipex);
		if (access_status == -2)
			break ;
		index++;
	}
	clean_split(paths);
	return (access_status);
}

int	parse_all_commands(t_pipe_d *pipex)
{
	int		access_status;
	int		cmd_index;

	cmd_index = 0;
	while (cmd_index < pipex->num_cmd)
	{
		access_status = parse_one_command(pipex, cmd_index);
		if (pipex->fd_inout[0] > -1 && cmd_index == 0)
		{
			if (access_status == -1)
				except_clean(pipex->cmd[cmd_index], pipex, CMD_NF);
			if (access_status == -2)
				except_clean(pipex->cmd[cmd_index], pipex, CMD_PERM);
		}
		except_middle_command(cmd_index, access_status, pipex);
		if (pipex->fd_inout[1] > -1 && cmd_index == pipex->num_cmd - 1)
		{
			if (access_status == -1)
				except_clean(pipex->cmd[cmd_index], pipex, CMD_NF_L);
			if (access_status == -2)
				except_clean(pipex->cmd[cmd_index], pipex, CMD_PERM_L);
		}
		cmd_index++;
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
			except_clean("malloc", pipex, MALLOC);
		}
		return (0);
	}
	else if (access_status == -2)
	{
		clean_split(cmd_paths);
		return (-2);
	}
	return (access_status);
}
