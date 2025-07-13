/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 07:41:05 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/12 14:39:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_delim(char c, char delim)
{
	if (c == delim)
		return (1);
	return (0);
}

static int	count_words(const char *s, char delim)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (!ft_is_delim(*s, delim) && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (ft_is_delim(*s, delim))
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_word(const char *s, char delim)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (s[len] && !ft_is_delim(s[len], delim))
		len++;
	word = malloc((sizeof(char)) * (len + 1));
	if (!word)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_split(char **result)
{
	int	i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free (result);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**result;

	i = 0;
	if (!s)
		return (0);
	result = malloc((sizeof(char *)) * (count_words(s, c) + 1));
	if (!result)
		return (0);
	while (*s)
	{
		if (!ft_is_delim(*s, c))
		{
			result[i] = alloc_word(s, c);
			if (!result[i++])
				return (free_split(result), NULL);
			while (*s && !ft_is_delim(*s, c))
				s++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
