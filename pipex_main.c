/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/04 13:48:30 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_it(char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_pipe_d	pipex;
	int			result;

	result = 0;
	initialize_pipe(&pipex, argc, argv, envp);
	open_fildes(&pipex);
	parse_commands(&pipex);
	pipex.fd = pipex.fd_inout[0];
	errno = 0;
	run_first_command(&pipex);
	run_last_command(&pipex);
	printf("How did it go: %d\n", result);
	except_clean(NULL, &pipex);
	if (argc > 0 && envp)
		argv[0][0] = 'a';
	return (0);
}

