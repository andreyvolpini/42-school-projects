/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:16:28 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 14:06:31 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "parser.h"
# include "execution.h"
# include "redirections.h"
# include "builtins.h"
# include <signal.h>
# include <limits.h>

# define BLUE "\001\033[38;2;0;0;255m\002"
# define YELLOW "\001\033[38;2;255;255;0m\002"
# define RESET  "\001\033[0m\002"
# define SYNTAX_ERROR "minishell: syntax error near unexpected token"

extern int	g_signal;

typedef struct s_vars
{
	char	*line;
	char	**nenv;
	char	*tmp;
	char	*prev;
	char	*full_line;
	int		len;
	char	*pwd;
	int		is_dir;
}	t_vars;

typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		in_pipeline;
	int		g_status;
}	t_shell;

typedef struct s_geral
{
	t_vars		vars;
	t_token		*tokens;
	t_token		*tmp;
	t_cmds		*cmds;
	t_gecmds	gecmds;
	t_geoper	geopers;
	t_env		*env;
	t_shell		sh;
}	t_geral;

void	free_arr(char **arr);
void	ft_close(t_geral *geral);
void	copy_env(t_geral *geral, char *env[]);
int		validate_syntax(t_token *tokens);
void	handler_sigint_child(int sig);
void	add_historic(t_geral *geral);

#endif
