/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 19:26:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 20:23:39 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 2
# define EXECUTE 4
# define WRITE 8
# define CMD_NF 16
# define CMD_NF_L 127
# define CMD_PERM 32
# define CMD_PERM_L 126
# define FILE_NF 64
# define FILE_PRM_L 128
# define FILE_PRM 256
# define DUP 8
# define DUP2 2
# define FORK 3
# define EXECVE 4
# define PIPE 5
# define MALLOC 6
# define OPEN 7

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipe_data
{
	int		fd;
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
	int		error;
	int		to_return;
}		t_pipe_d;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c, int *words);
void	*clean_split(char **str);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
int		measure_array(char **arr);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		except_clean(char *name, t_pipe_d *pipex, int err_code);
int		parse_all_commands(t_pipe_d *pipex);
void	except_middle_command(int cmd_index, int access_status, t_pipe_d *pipex);
void	initialize_pipe(t_pipe_d *pipex, int argc, char **argv, char **envp);
int		check_access(char *cmd, int mode);
void	run_first_command(t_pipe_d *pipex);
void	run_last_command(t_pipe_d *pipex);
void	run_middle_command(int index_cmd, t_pipe_d *pipex);

#endif
