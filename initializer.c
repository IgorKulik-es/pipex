/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:04:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/07 16:52:34 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	asign_memory_pipex(t_pipe_d *pipex, int argc, char **argv);

void	initialize_pipe(t_pipe_d *pipex, int argc, char **argv, char **envp)
{
	pipex->args = NULL;
	pipex->cmd = NULL;
	pipex->paths = NULL;
	pipex->pids = NULL;
	pipex->fd = NULL;
	pipex->num_cmd = argc - 3;
	pipex->path_size = 0;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->fd_inout[0] = -1;
	pipex->fd_inout[1] = -1;
	pipex->error = 0;
	pipex->to_return = 0;
	if (pipex->num_cmd != 2)
	{
		write(2, "pipex: wrong number of arguments\n", 33);
		exit(EXIT_FAILURE);
	}
	pipex->files[0] = argv[1];
	pipex->files[1] = argv[argc - 1];
	asign_memory_pipex(pipex, argc, argv);
}

static void	asign_memory_pipex(t_pipe_d *pipex, int argc, char **argv)
{
	int	words_dummy;

	words_dummy = 0;
	pipex->cmd = (char **)malloc((pipex->num_cmd + 1) * sizeof(char *));
	pipex->args = (char ***)malloc((pipex->num_cmd + 1) * sizeof(char **));
	pipex->pids = (int *)malloc((pipex->num_cmd) * sizeof(int));
	pipex->fd = (int *)malloc((pipex->num_cmd - 1) * sizeof(int));
	if (pipex->cmd == NULL || pipex->args == NULL
		|| pipex->pids == NULL || pipex->fd == NULL)
		except_clean("malloc", pipex, MALLOC);
	pipex->cmd[pipex->num_cmd] = NULL;
	pipex->args[pipex->num_cmd] = NULL;
	argc--;
	while (--argc >= 2)
	{
		pipex->args[argc - 2] = ft_split(argv[argc],
				' ', &words_dummy);
		if (pipex->args[argc - 2] == NULL)
			except_clean("malloc", pipex, MALLOC);
		pipex->cmd[argc - 2] = ft_strjoin(pipex->args[argc - 2][0], "", "");
		if (pipex->cmd[argc - 2] == NULL && pipex->args[argc - 2][0] != NULL)
			except_clean("malloc", pipex, MALLOC);
	}
}

int	check_access(char *cmd, int mode)
{
	int	access_status;

	if (cmd == NULL)
		return (-1);
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
