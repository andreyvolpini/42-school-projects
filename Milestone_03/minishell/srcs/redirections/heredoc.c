/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:46:46 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/21 11:16:22 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint_child(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit\n", 5);
	else if (sig == SIGINT)
		write(1, "\n", 1);
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_sigint);
	signal(SIGTSTP, SIG_IGN);
}

static void	handler_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = 2;
	close(STDIN_FILENO);
}

static void	heredoc_child(t_geral *geral, int i, int pipefd[2])
{
	char	*line;
	int		len;

	signal(SIGINT, handler_sigint_heredoc);
	len = ft_strlen(geral->geopers.opers[i].value);
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal == 2)
		{
			free(line);
			break ;
		}
		if (ft_strncmp(line, geral->geopers.opers[i].value, len + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	cleanup_exit(geral);
	exit(0);
}

int	heredoc(t_geral *geral, int i)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		heredoc_child(geral, i, pipefd);
	else if (pid > 0)
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			if (geral->geopers.opers[i].value)
				free(geral->geopers.opers[i].value);
			geral->geopers.opers[i].value = NULL;
			return (close(pipefd[0]), -2);
		}
		return (pipefd[0]);
	}
	return (init_signal(), -1);
}
