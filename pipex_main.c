/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 20:22:22 by ikulik           ###   ########.fr       */
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
	result = run_one_command(0, &pipex);
	printf("How did it go: %d\n", result);
	//printf("Cmds :%s, %s\nfile names:%s, %s\n, cmd nums: %d, %d\n", pipex.cmd[0], pipex.cmd[1], pipex.files[0], pipex.files[1], pipex.num_args[0], pipex.num_args[1]);
	//do_it(argv);
	errno = 0;
	except_clean("end", &pipex);
	if (argc > 0 && envp)
		argv[0][0] = 'a';
	return (0);
}

