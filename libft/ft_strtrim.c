/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:59:50 by avolpini          #+#    #+#             */
/*   Updated: 2025/04/10 07:28:20 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_str = malloc(sizeof(char) * ((end - start) + 1));
	if (!trimmed_str)
		return (0);
	i = 0;
	while (start < end)
		trimmed_str[i++] = s1[start++];
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
