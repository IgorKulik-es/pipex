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
	initialize_pipe(&pipex, argc, argv);
	result = find_command(0, envp, &pipex);
	printf("Searching %s\n", pipex.cmd[0]);
	printf("Command found %s\n", pipex.cmd[0]);
	printf("Do I have access: %d\n", result);
	//printf("Cmds :%s, %s\nfile names:%s, %s\n, cmd nums: %d, %d\n", pipex.cmd[0], pipex.cmd[1], pipex.files[0], pipex.files[1], pipex.num_args[0], pipex.num_args[1]);
	//do_it(argv);
	except_clean("End", &pipex);
	if (argc > 0 && envp)
		argv[0][0] = 'a';
	return (0);
}


void	do_it(char **argv)
{
	int		fd[2];
	//char	*test;

	printf("Found file: %d, have read rights: %d\n", access(argv[1], F_OK), access(argv[1], R_OK));
	//fd[0] = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0622);
	fd[1] = open(argv[1], O_RDONLY);
	//dup2(fd[0], 1);
	//dup2(fd[1], 0);
	perror(argv[1]);
	//close(fd[0]);
	close(fd[1]);
}
