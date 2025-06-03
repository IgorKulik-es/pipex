/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/03 19:53:42 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 2
# define EXECUTE 4
# define WRITE 8

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipe_data
{
	int		fd[2];
	int		stdio[2];
	int		fd_inout[2];
	int		num_cmd;
	char	*files[2];
	int		*num_args;
	char	**cmd;
	char	***args;
	char	**paths;
	char	**argv;
	char	**envp;
	int		path_size;
}		t_pipe_d;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c, int *words);
void	*clean_split(char **str);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
int		measure_array(char **arr);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		parse_commands(t_pipe_d *pipex);
int		run_one_command(int index_cmd, t_pipe_d *pipex);
int		except_clean(char *name, t_pipe_d *pipex);
void	initialize_pipe(t_pipe_d *pipex, int argc, char **argv, char **envp);
int		check_access(char *cmd, int mode);
int		open_fildes(t_pipe_d *pipex);

#endif

