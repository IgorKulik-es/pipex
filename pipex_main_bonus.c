/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:25:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/07 15:23:55 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_d	pipex;
	int			index;

	index = 1;
	initialize_pipe(&pipex, argc, argv, envp);
	check_input(&pipex);
	parse_all_commands(&pipex);
	run_first_command(&pipex);
	while (index < pipex.num_cmd - 1)
	{
		run_middle_command(index, &pipex);
		index++;
	}
	run_last_command(&pipex);
	main_waiter(&pipex);
	except_clean(NULL, &pipex, 0);
	return (pipex.to_return);
}
