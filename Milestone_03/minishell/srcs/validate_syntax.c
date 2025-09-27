/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ginfranc <ginfranc@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:26:54 by ginfranc          #+#    #+#             */
/*   Updated: 2025/09/26 13:57:17 by ginfranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_type_for_str(t_token_type type)
{
	if (type == T_PIPE)
		return ("|");
	if (type == T_IN)
		return ("<");
	if (type == T_OUT)
		return (">");
	if (type == T_HEREDOC)
		return ("<<");
	if (type == T_APPEND)
		return (">>");
	return ("UNKNOWN");
}

void	print_unexpected_token(t_token *tok)
{
	ft_putstr_fd(" `", 2);
	if (!tok)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token_type_for_str(tok->type), 2);
	ft_putendl_fd("'", 2);
}

void	error_syntax(t_token *tmp, t_token *prev)
{
	ft_putstr_fd(SYNTAX_ERROR, 2);
	if (tmp->type == T_PIPE)
	{
		if (!prev)
			print_unexpected_token(tmp);
		else if (!tmp->next)
			print_unexpected_token(NULL);
		else if (tmp->next->type == T_PIPE)
			print_unexpected_token(tmp->next);
		else
			print_unexpected_token(tmp);
	}
	else if (tmp->type == T_IN || tmp->type == T_OUT
		|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
	{
		if (!tmp->next)
			print_unexpected_token(NULL);
		else
			print_unexpected_token(tmp->next);
	}
	else
		print_unexpected_token(NULL);
}

int	validate_syntax_utils(t_token *tmp, t_token *prev)
{
	if (tmp->type == T_PIPE)
	{
		if (!prev || !tmp->next || tmp->next->type == T_PIPE)
		{
			error_syntax(tmp, prev);
			return (1);
		}
	}
	if (tmp->type == T_IN || tmp->type == T_OUT
		|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
	{
		if (!tmp->next || tmp->next->type != T_WORD)
		{
			error_syntax(tmp, prev);
			return (1);
		}
		else if (tmp->next->value
			&& ft_strncmp(tmp->next->value, " ", 2) == 0)
		{
			error_syntax(tmp, prev);
			return (1);
		}
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*tmp;
	t_token	*prev;

	if (!tokens)
		return (0);
	tmp = tokens;
	prev = NULL;
	while (tmp)
	{
		if (validate_syntax_utils(tmp, prev) == 1)
			return (1);
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
