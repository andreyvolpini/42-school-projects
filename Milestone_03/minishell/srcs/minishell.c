/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:15:09 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 13:56:55 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	init_geral(t_geral *geral, char *env[])
{
	ft_memset(geral, 0, sizeof(*geral));
	copy_env(geral, env);
	geral->sh.env = env_init(env);
	geral->vars.pwd = getcwd(NULL, 0);
	if (!geral->sh.env)
	{
		env_set(&geral->sh.env, "_", "/usr/bin/env", 1);
		env_set(&geral->sh.env, "SHLVL", "1", 1);
		env_set(&geral->sh.env, "PWD", geral->vars.pwd, 1);
	}
}

static int	handle_empty_or_ws_line(t_geral *geral)
{
	if (ft_strlen(geral->vars.line) == 0 || is_str_whitespace(geral->vars.line))
	{
		free(geral->vars.line);
		geral->vars.line = NULL;
		return (1);
	}
	return (0);
}

static void	open_unclosed_quotes(t_geral *geral)
{
	char	*extra;

	while (has_unclosed_quotes(geral->vars.line))
	{
		extra = readline("> ");
		if (!extra)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking"
				" for matching `\"'\n", 2);
			free(geral->vars.line);
			geral->vars.line = NULL;
			geral->sh.g_status = 2;
			return ;
		}
		geral->vars.line = ft_strjoin_free(geral->vars.line, "\n");
		geral->vars.line = ft_strjoin_free(geral->vars.line, extra);
		free(extra);
	}
}

static int	handle_tokens(t_geral *geral)
{
	geral->tokens = tokenize(geral->vars.line, &geral->sh);
	if (validate_syntax(geral->tokens))
	{
		geral->sh.g_status = 2;
		free(geral->vars.line);
		geral->vars.line = NULL;
		free_tokens(geral->tokens);
		geral->tokens = NULL;
		return (1);
	}
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	t_geral	geral;

	(void)ac;
	(void)av;
	init_geral(&geral, env);
	while (1)
	{
		init_signal();
		geral.vars.line = readline(BLUE "mini" RESET YELLOW "shell" RESET "$ ");
		open_unclosed_quotes(&geral);
		if (!geral.vars.line)
			builtin_exit(NULL, &geral);
		if (handle_empty_or_ws_line(&geral))
			continue ;
		add_historic(&geral);
		if (handle_tokens(&geral))
			continue ;
		if (finder_opers(&geral) != 0)
			handle_opers_errors(&geral);
		create_cmds(&geral, -1);
		cleanup_iteration(&geral);
	}
	return (geral.sh.g_status);
}
