/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:13:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 23:13:47 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(t_pipe_d *pipex)
{
	int	access_status;

	access_status = check_access(pipex->files[0], READ);
	if (access_status != 0)
		except_clean(pipex->files[0], pipex);
	access_status = check_access(pipex->files[1], WRITE);
	if (access_status == -2)
		except_clean(pipex->files[1], pipex);
	return (0);
}

int	open_fildes(t_pipe_d *pipex)
{
	check_files(pipex);
	pipex->fd_inout[0] = open(pipex->files[0], O_RDONLY);
	if (pipex->fd_inout[0] < 0)
		except_clean(pipex->files[0], pipex);
	pipex->fd_inout[1] = open(pipex->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0622);
	if (pipex->fd_inout[1] < 0)
		except_clean(pipex->files[1], pipex);
	pipex->stdio[0] = dup(0);
	if (pipex->stdio[0] == -1)
		except_clean("dup", pipex);
	pipex->stdio[1] = dup(1);
	if (pipex->stdio[1] == -1)
		except_clean("dup", pipex);
	return (0);
}