/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:11:26 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 13:59:28 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_geral *g, int i)
{
	int	status;

	status = 0;
	status = run_builtin(g, &g->cmds[i]);
	cleanup_exit(g);
	exit(status);
}

void	execute_all_utils(t_geral *g, pid_t pid, int i, int pipefd[2][2])
{
	signal(SIGQUIT, handler_sigint_child);
	signal(SIGINT, handler_sigint_child);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (i > 0 && pipefd[(i + 1) % 2][0] != -1)
			dup2(pipefd[(i + 1) % 2][0], STDIN_FILENO);
		if (i < g->gecmds.n_cmds - 1 && pipefd[i % 2][1] != -1)
			dup2(pipefd[i % 2][1], STDOUT_FILENO);
		if (g->cmds[i].fd_in == -2 || g->cmds[i].fd_out == -2)
			free_and_close(g);
		dup2(g->cmds[i].fd_in, STDIN_FILENO);
		dup2(g->cmds[i].fd_out, STDOUT_FILENO);
		close_all_pipes(g, pipefd, i);
		if ((!g->cmds[i].cmd || !g->cmds[i].cmd[0]
				|| g->cmds[i].cmd[0][0] == '\0') || g->cmds[i].error == -1)
			free_empty(g, i);
		if (is_builtin(&g->cmds[i]) || is_parent_builtin(&g->cmds[i]))
			execute_child(g, i);
		else
			execution_in_child(g, i);
	}
	else
		close_pipes(pipefd, i);
}

void	wait_child(pid_t last_pid, t_geral *g)
{
	int		status;
	pid_t	pid;

	pid = 1;
	status = 0;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status))
				g->sh.g_status = 128 + WTERMSIG(status);
			else
				g->sh.g_status = WEXITSTATUS(status);
		}
	}
}

void	execute_all(t_geral *g, int i)
{
	int		pipefd[2][2];
	pid_t	pid;
	pid_t	last_pid;

	last_pid = -1;
	init_pipes(pipefd);
	while (++i < g->gecmds.n_cmds)
	{
		if (i < g->gecmds.n_cmds - 1 && pipe(pipefd[i % 2]) == -1)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		execute_all_utils(g, pid, i, pipefd);
		last_pid = pid;
	}
	close_all_pipes(g, pipefd, -1);
	wait_child(last_pid, g);
}

void	count_commands(t_geral *geral, t_token *tokens, int status)
{
	int		found_word;

	found_word = 0;
	geral->gecmds.n_cmds = 0;
	while (tokens)
	{
		if (tokens->type == T_WORD)
			found_word = 1;
		else if (tokens->type == T_PIPE && found_word)
		{
			geral->gecmds.n_cmds++;
			found_word = 0;
		}
		tokens = tokens->next;
	}
	if (found_word)
		geral->gecmds.n_cmds++;
	if (status == 1)
		finder_path(geral);
}
