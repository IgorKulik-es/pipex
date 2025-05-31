/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:33:12 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 17:50:56 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_path(char **envp)
{
	char	**env_buffer;

	env_buffer = envp;
	while (*env_buffer)
	{
		if (ft_strncmp("PATH", *env_buffer, 4) == 0)
			break ;
		env_buffer++;
	}
	if (*env_buffer == NULL)
		return (NULL);
	env_buffer = ft_split(*env_buffer, ':');
	if (env_buffer == NULL)
		return (NULL);
	printf("Line found %s\n", env_buffer[1]);
	return (env_buffer);
}


