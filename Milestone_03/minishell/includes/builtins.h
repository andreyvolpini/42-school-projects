/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:10:41 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 09:10:41 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_assign_op
{
	NAME_ONLY,
	ASSIGN,
	APPEND,
}	t_assign_op;

typedef struct s_assign
{
	const char	*name;
	size_t		name_len;
	const char	*value;
	t_assign_op	op;
}	t_assign;

/*echo.c*/
int		builtin_echo(t_cmds *cmd);

/*exit.c*/
int		builtin_exit(t_cmds *cmd, t_geral *geral);
void	cleanup_iteration(t_geral *geral);
void	cleanup_exit(t_geral *geral);

/*exit_utils.c*/
int		is_valid_integer(const char *s);
int		ft_atoll(const char *s, long long *out);
int		init_parse(const char **ps, int *sign);
int		negative_parse(unsigned long long acum, long long *out);

/*env.c*/
int		builtin_env(t_cmds *cmd, t_env *env);
t_env	*env_init(char **envp);
t_env	*env_find(t_env *env, const char *key);

/*env_utils.c*/
int		env_size(t_env *env);
char	**env_to_array(t_env *env);
t_env	*env_node_from_entry(const char *entry);
void	free_env_list(t_env *head);

/*pwd.c*/
int		builtin_pwd(t_geral *geral);

/*cd.c*/
int		builtin_cd(char **args, t_geral *geral);

/*export.c*/
int		builtin_export(t_geral *geral, t_cmds *cmd);

/*export_env.c*/
char	*env_get_value(t_env *env, const char *key);
int		env_set(t_env **penv, const char *key, const char *value, int exported);
void	bubble_sort_env_array(t_env **arr, size_t n);

/*export_utils.c*/
int		is_first_ok(int c);
int		is_rest_ok(int c);
int		is_valid_identifier(const char *s, int allow_assign);
void	split_assign(const char *arg, t_assign *out);
int		cmp_env_ptrs(const void *a, const void *b);

/*export_create.c*/
int		exp_app_one(t_geral *geral, char *arg, int *had_invalid);

/*unset.c*/
int		builtin_unset(t_geral *geral, t_cmds *cmd);

#endif