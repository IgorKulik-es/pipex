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

void	do_it(char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
/* 	int	fd[2];*/
	char	*result;

	result = find_command(argv[1], envp);
	printf("Do I have access: %s\n", result);
	free(result);
	//do_it(argv, envp);
	if (argc > 0)
		argv[0][0] = 'a';
	return (0);
}


void	do_it(char **argv, char **envp)
{
	int		fd[2];
	int		error;
	char	**env_var;

	error = 1000;
	env_var = envp;
	fd[0] = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0622);
	fd[1] = open(argv[1], O_RDONLY);
	dup2(fd[0], 1);
	dup2(fd[1], 0);
	env_var = create_cmd_path(argv[3], envp);
	printf("Trying command %s\n", env_var[4]);
	error = try_one_command(env_var[4], &argv[3], envp);
	clean_split(env_var);
	printf("Tried with error %d\n", error);
	close(fd[0]);
	close(fd[1]);
}
