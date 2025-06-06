/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 20:26:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_d	pipex;
	int			result;

	result = 0;
	initialize_pipe(&pipex, argc, argv, envp);
	result += parse_all_commands(&pipex);
	pipex.fd = pipex.fd_inout[0];
	errno = 0;
	run_first_command(&pipex);
	run_middle_command(1, &pipex);
	run_last_command(&pipex);
	except_clean(NULL, &pipex, 0);
	return (pipex.to_return);
}
