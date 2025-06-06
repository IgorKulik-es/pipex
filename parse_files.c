/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:13:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 20:14:57 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	check_input(t_pipe_d *pipex)
{
	int	access_status;

	access_status = check_access(pipex->files[0], READ);
	if (access_status == -1)
		except_clean(pipex->files[0], pipex, FILE_NF);
	if (access_status == -2)
		except_clean(pipex->files[0], pipex, FILE_PRM);
	if (access_status == 0)
		pipex->fd_inout[0] = open(pipex->files[0], O_RDONLY);
	if (pipex->fd_inout[0] < 0 && (access_status == 0))
		except_clean("open", pipex, OPEN);
	return (access_status);
}

int	check_output(t_pipe_d *pipex)
{
	int	access_status;

	access_status = check_access(pipex->files[1], WRITE);
	if (access_status == -2)
		except_clean(pipex->files[1], pipex, FILE_PRM_L | FILE_PRM);
	pipex->fd_inout[1] = open(pipex->files[1],
			O_WRONLY | O_CREAT | O_TRUNC, 0622);
	if (pipex->fd_inout[1] < 0 && (access_status == 0))
		except_clean("open", pipex, OPEN);
	return (access_status);
}
