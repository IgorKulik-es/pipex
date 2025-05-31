/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 19:13:39 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*clean_split(char **str);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
int		measure_array(char **arr);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	**parse_path(char **envp);
char	**create_cmd_path(char *cmd, char **envp);
int		try_one_command(char *cmd, char **argv, char **envp);

#endif

