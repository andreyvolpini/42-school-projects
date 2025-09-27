/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:11:05 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 09:11:05 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

typedef enum e_quote
{
	NORMAL,
	IN_SINGLE,
	IN_DOUBLE
}	t_quote;

/* ----- Internal hepers (normalize.c) ----- */
typedef struct s_norm_ctx
{
	char	*new_cmd;
	int		*j;
	t_quote	*q;
}	t_norm_ctx;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_HEREDOC,
	T_APPEND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_range
{
	size_t	start;
	size_t	end;
}	t_range;

typedef struct s_expand_ctx
{
	const char	*s;
	t_shell		*sh;
	char		**out;
	t_quote		q;
	size_t		i;
}	t_expand_ctx;

/*quote.c*/
void		update_quote_state(t_quote *q, char c);
int			copy_quote_adv(const char *s, char **out, size_t *i, t_quote *q);
int			has_unclosed_quotes(const char *line);
char		*ft_strjoin_free(char *s1, const char *s2);
void		handle_opers_errors(t_geral *geral);

/*tokenize.c*/
t_token		*tokenize(const char *line, t_shell *sh);

/*token_list.c*/
t_token		*new_token(char *value, t_token_type type, t_quote quote);
void		add_new_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *head);
void		detect_quote_flags(const char *raw, int *in_single, int *in_double);

/*token_utils.c*/
int			add_op_token(t_token **list, const char *raw, int in_s, int in_d);
int			add_word_t(t_token **list, const char *raw, t_shell *sh, t_quote q);

/*strip_quotes.c*/
char		*strip_outside_quotes(const char *src, size_t len);

/*scanner.c*/
int			get_position_quote(const char *str, size_t *pos, t_range *r);
int			is_str_whitespace(const char *s);

/*normalize.c*/
char		*normalize_cmd(const char *cmd);

/*expand_utils.c*/
char		*extract_name(const char *s, size_t *len);
char		*append_str(char *dst, const char *src);
char		*append_char(char *dst, char c);
const char	*ctx_getenv(t_shell *sh, const char *name);
int			expand_word_step(t_expand_ctx *ctx);

/*expand.c*/
char		*expand_word(const char *s, t_shell *sh);
int			dollar_dispatch(const char *s, char **out, size_t *i, t_shell *sh);

#endif
