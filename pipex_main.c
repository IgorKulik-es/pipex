/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 19:36:01 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_it(char **argv);

int	main(int argc, char **argv, char **envp)
{
/* 	int	fd[2];*/
	char	*result;

	result = find_command(argv[1], envp);
	printf("Do I have access: %s\n", result);
	free(result);
	do_it(argv);
	if (argc > 0)
		argv[0][0] = 'a';
	return (0);
}


void	do_it(char **argv)
{
	//int		fd[2];	
	//char	*test;

	printf("Found file: %d, have exec rights: %d\n", access(argv[1], F_OK), access(argv[1], X_OK));
	//fd[0] = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0622);
	//fd[1] = open(argv[1], O_RDONLY);
	//dup2(fd[0], 1);
	//dup2(fd[1], 0);
	printf("My error: %s\n", strerror(errno));
	//close(fd[0]);
	//close(fd[1]);
}
