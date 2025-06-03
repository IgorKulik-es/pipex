/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:33:12 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 20:21:15 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_access(char *cmd, int mode);
static int	get_cmd(int cmd_index, int i, char **cmd_paths, t_pipe_d *pipex);

char	**parse_path(char **envp, t_pipe_d *pipex)
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
	env_buffer = ft_split(*env_buffer, ':', &pipex->path_size);
	if (env_buffer == NULL)
		except_clean("malloc", pipex);
	return (env_buffer);
}

char	**create_cmd_path(char *cmd, char **envp, t_pipe_d *pipex)
{
	char	**result;
	int		index;

	index = 0;
	if (pipex->paths == NULL)
		pipex->paths = parse_path(envp, pipex);
	if (pipex->paths == NULL)
		except_clean(cmd, pipex);
	result = (char **)malloc((pipex->path_size + 1) * sizeof(char *));
	if (result == NULL)
		except_clean("malloc", pipex);
	while (pipex->paths[index])
	{
		result[index] = ft_strjoin(pipex->paths[index], "/", cmd);
		if (result[index] == NULL)
		{
			clean_split(result);
			except_clean("malloc", pipex);
		}
		index++;
	}
	result[index] = NULL;
	return (result);
}

int	find_command(int cmd_index, char **envp, t_pipe_d *pipex)
{
	char	**paths;
	char	*result;
	int		index;
	int		have_access;

	index = 0;
	result = NULL;
	have_access = check_access(pipex->cmd[cmd_index], EXECUTE);
	if (have_access == 0)
		return (0);
	if (have_access == -2)
		except_clean(pipex->cmd[cmd_index], pipex);
	paths = create_cmd_path(pipex->cmd[cmd_index], envp, pipex);
	while (paths[index] && have_access != 0)
	{
		have_access = get_cmd(cmd_index, index, paths, pipex);
		index++;
	}
	clean_split(paths);
	if (have_access == 0)
		return (0);
	return (-1);
}

static int	get_cmd(int cmd_index, int i, char **cmd_paths, t_pipe_d *pipex)
{
	int	have_access;

	have_access = check_access(cmd_paths[i], EXECUTE);
	if (have_access == 0)
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
	else if (have_access == -2)
	{
		clean_split(cmd_paths);
		except_clean(cmd_paths[cmd_index], pipex);
	}
	return (have_access);
}


static int	check_access(char *cmd, int mode)
{
	int	have_access;

	have_access = access(cmd, F_OK);
	if (have_access == -1)
		return (-1);
	if (mode == READ)
		have_access = access(cmd, R_OK);
	if (mode == EXECUTE)
		have_access = access(cmd, X_OK);
	if (have_access == -1)
		return (-2);
	return (0);
}
