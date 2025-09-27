/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:48 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:48 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_num_arg(t_geral *geral, char *arg);

int	check_exit_args(t_cmds *cmd, t_geral *geral, int ac, long long *num)
{
	int		idx;
	char	*arg;

	idx = 1;
	if (ac > 1 && cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "--", 3) == 0)
		idx = 2;
	if (idx >= ac)
	{
		cleanup_exit(geral);
		exit((unsigned char)geral->sh.g_status);
	}
	arg = cmd->cmd[idx];
	if (!ft_atoll(arg, num))
		exit_num_arg(geral, arg);
	if (ac > idx + 1)
	{
		geral->sh.g_status = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		cleanup_iteration(geral);
		return (1);
	}
	return (0);
}

int	builtin_exit(t_cmds *cmd, t_geral *geral)
{
	int			ac;
	long long	num;

	ac = 0;
	printf("exit\n");
	while (cmd && cmd->cmd && cmd->cmd[ac])
		ac++;
	if (ac == 2 && cmd->cmd[1] && ft_strncmp(cmd->cmd[1], "--", 3) == 0)
	{
		cleanup_exit(geral);
		exit((unsigned char)geral->sh.g_status);
	}
	if (ac == 1 || ac == 0)
	{
		cleanup_exit(geral);
		exit((unsigned char)geral->sh.g_status);
	}
	if (check_exit_args(cmd, geral, ac, &num))
		return (1);
	cleanup_exit(geral);
	exit((unsigned char)num);
}

void	cleanup_iteration(t_geral *geral)
{
	if (!geral)
		return ;
	if (geral->tokens)
	{
		free_tokens(geral->tokens);
		geral->tokens = NULL;
	}
	if (geral->cmds)
	{
		free_cmds(geral);
		geral->cmds = NULL;
	}
	if (geral->vars.line)
	{
		free(geral->vars.line);
		geral->vars.line = NULL;
	}
	free_redirec(geral);
}

void	cleanup_exit(t_geral *geral)
{
	if (!geral)
		return ;
	cleanup_iteration(geral);
	rl_clear_history();
	if (geral->gecmds.path)
	{
		free_arr(geral->gecmds.path);
		geral->gecmds.path = NULL;
	}
	if (geral->sh.env)
	{
		free_env_list(geral->sh.env);
		geral->sh.env = NULL;
	}
	if (geral->vars.nenv)
	{
		free_arr(geral->vars.nenv);
		geral->vars.nenv = NULL;
	}
	if (geral->vars.pwd)
	{
		free(geral->vars.pwd);
		geral->vars.pwd = NULL;
	}
	ft_close(geral);
}

static void	exit_num_arg(t_geral *geral, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	cleanup_exit(geral);
	exit(2);
}
