/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:14:52 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 14:00:11 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	int				fd_in;
	int				fd_out;
	int				error;
}	t_cmds;

typedef struct s_gecmds
{
	int		n_cmds;
	char	**path;
}	t_gecmds;

void	execute_cmd(t_geral	*geral);

int		cmds_test(t_geral *geral, t_cmds *cmds);
void	finder_path(t_geral *geral);
void	count_commands(t_geral *geral, t_token *tokens, int status);
char	**tokenlist_to_array(t_token *token_list);
void	create_cmds(t_geral *geral, int i);
void	close_all_pipes(t_geral *geral, int pipefd[2][2], int i);
void	init_pipes(int pipe[2][2]);
void	close_pipes(int pipefd[2][2], int i);
void	handler_sigint(int sig);
void	execute_all(t_geral *g, int i);
void	execute_all_utils(t_geral *g, pid_t pid, int i, int pipefd[2][2]);
int		is_directory(t_cmds *cmds);
void	free_cmds(t_geral *geral);
void	close_pipered(t_geral *geral);
void	print_erro(int retorno, t_cmds *cmds, t_geral *geral);
void	execution_and_free(t_geral *geral);
void	set_fds(t_geral *geral);
void	execution_in_child(t_geral *g, int i);
void	init_signal(void);
void	free_and_close(t_geral *g);

/*run_builtin.c*/
int		run_builtin(t_geral *geral, t_cmds *cmd);
int		is_builtin(t_cmds *cmd);
int		is_parent_builtin(t_cmds *cmd);
void	free_empty(t_geral *g, int i);

#endif
