/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:15:39 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/19 21:11:57 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	copy_env(t_geral *geral, char *env[])
{
	int	index;

	index = 0;
	while (env[index])
		index++;
	geral->vars.nenv = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (env[index])
	{
		geral->vars.nenv[index] = ft_strdup(env[index]);
		index++;
	}
	geral->vars.nenv[index] = NULL;
}

void	free_arr(char **arr)
{
	int	index;

	index = 0;
	if (!arr)
		return ;
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
}

void	ft_close(t_geral *geral)
{
	free_arr(geral->vars.nenv);
	free(geral->vars.pwd);
}

void	add_historic(t_geral *geral)
{
	add_history(geral->vars.line);
	if (g_signal != 0)
	{
		geral->sh.g_status = 128 + g_signal;
		g_signal = 0;
	}
}
