/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:04:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/04 16:23:13 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	asign_memory_pipex(t_pipe_d *pipex, int argc, char **argv);

void	initialize_pipe(t_pipe_d *pipex, int argc, char **argv, char **envp)
{
	pipex->args = NULL;
	pipex->cmd = NULL;
	pipex->paths = NULL;
	pipex->num_cmd = argc - 3;
	pipex->num_args = NULL;
	pipex->path_size = 0;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->fd_inout[0] = -1;
	pipex->fd_inout[1] = -1;
	pipex->fd = -1;
	pipex->stdio[0] = 0;
	pipex->stdio[1] = 1;
	pipex->error = 0;
	if (pipex->num_cmd != 2)
	{
		perror("Wrong number of arguments!");
		exit(EXIT_FAILURE);
	}
	pipex->files[0] = argv[1];
	pipex->files[1] = argv[argc - 1];
	asign_memory_pipex(pipex, argc, argv);
}

static void	asign_memory_pipex(t_pipe_d *pipex, int argc, char **argv)
{
	pipex->files[0] = argv[1];
	pipex->files[1] = argv[4];
	pipex->cmd = (char **)malloc((pipex->num_cmd + 1) * sizeof(char *));
	pipex->args = (char ***)malloc((pipex->num_cmd + 1) * sizeof(char **));
	pipex->num_args = (int *)malloc(pipex->num_cmd * sizeof(int));
	if (pipex->cmd == NULL || pipex->args == NULL || pipex->num_args == NULL)
		except_clean("malloc", pipex);
	pipex->cmd[pipex->num_cmd] = NULL;
	pipex->args[pipex->num_cmd] = NULL;
	argc--;
	while (--argc >= 2)
	{
		pipex->args[argc - 2] = ft_split(argv[argc], ' ', &pipex->num_args[argc - 2]);
		if (pipex->args[argc - 2] == NULL)
			except_clean("malloc", pipex);
		pipex->cmd[argc - 2] = ft_strjoin(pipex->args[argc - 2][0], "", "");
		if (pipex->cmd[argc - 2] == NULL && pipex->args[argc - 2][0] != NULL)
			except_clean("malloc", pipex);
	}
}
