/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/07 17:29:38 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_d	pipex;

	initialize_pipe(&pipex, argc, argv, envp);
	check_input(&pipex);
	check_output(&pipex);
	parse_all_commands(&pipex);
	pipex.fd[0] = pipex.fd_inout[0];
	errno = 0;
	run_first_command(&pipex);
	run_last_command(&pipex);
	main_waiter(&pipex);
	except_clean(NULL, &pipex, 0);
	return (pipex.to_return);
}
