/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:52:18 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:52:18 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_nflag(const char *s);

int	builtin_echo(t_cmds *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->cmd[i] && is_valid_nflag(cmd->cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

static int	is_valid_nflag(const char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
