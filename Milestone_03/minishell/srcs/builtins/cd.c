/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:32:21 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/22 11:50:34 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(t_cmds *cmds)
{
	struct stat	st;

	if (stat(cmds->cmd[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			if (cmds->cmd[0][ft_strlen(cmds->cmd[0]) - 1] == '/')
				return (1);
			else if (cmds->cmd[0][0] == '/')
				return (1);
			else if (cmds->cmd[0][0] == '.')
				return (1);
			else
				return (2);
		}
	}
	return (0);
}

int	count_args(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

const char	*create_path(char **args, t_geral *geral)
{
	const char	*path;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		path = ctx_getenv(&geral->sh, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
	}
	else
	{
		if (ft_strncmp(args[1], "-", 2) == 0)
		{
			path = ctx_getenv(&geral->sh, "OLDPWD");
			if (path)
				printf("%s\n", path);
		}
		else
			path = args[1];
	}
	return (path);
}

void	ft_getcwd(t_geral *geral)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: getcwd");
		cwd = ft_strjoin(ctx_getenv(&geral->sh, "PWD"), "/..");
	}
	env_set(&geral->sh.env, "OLDPWD", ctx_getenv(&geral->sh, "PWD"), 1);
	env_set(&geral->sh.env, "PWD", cwd, 1);
	if (geral->vars.pwd)
		free(geral->vars.pwd);
	geral->vars.pwd = ft_strdup(cwd);
	free(cwd);
}

int	builtin_cd(char **args, t_geral *geral)
{
	const char	*path;
	int			ac;

	ac = count_args(args);
	if (ac > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	path = create_path(args, geral);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	ft_getcwd(geral);
	return (0);
}
