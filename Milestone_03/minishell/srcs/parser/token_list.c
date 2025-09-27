/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@udent.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:54:03 by avolpini          #+#    #+#             */
/*   Updated: 2025/09/13 08:54:03 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type, t_quote quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->quote = quote;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	if (value && !token->value)
		return (free(token), NULL);
	token->next = NULL;
	return (token);
}

void	add_new_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token)
		return ;
	if (!head || !*head)
	{
		if (head)
			*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		free(tmp);
	}
}

void	detect_quote_flags(const char *raw, int *in_single, int *in_double)
{
	size_t	len;

	*in_single = 0;
	*in_double = 0;
	if (!raw)
		return ;
	len = ft_strlen(raw);
	if (len >= 2 && raw[0] == '\''
		&& *in_double == 0 && raw[len - 1] == '\'')
		*in_single = 1;
	else if (len >= 2 && raw[0] == '"'
		&& *in_single == 0 && raw[len - 1] == '"')
		*in_double = 1;
}
