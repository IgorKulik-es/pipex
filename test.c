/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:51:01 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/01 13:51:01 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv)
{
	int	index;
	
	index = 1;
	if (argc == 1)
		return (1);
	while (index < argc)
	{
		printf("%s ", argv[index]);
		index++;
	}
	printf("\n");
	return (0);
}