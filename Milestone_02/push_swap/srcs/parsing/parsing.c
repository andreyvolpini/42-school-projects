/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolpini <avolpini@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:38 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 16:32:38 by avolpini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

/*
--> alocar um array *original;
--> verificar se não tem números repetidos;
--> verificar se algum caracter não é número;
*/
int	*alloc_array(int count, char **values)
{
	int		*original;
	int		i;
	long	n;

	original = malloc(sizeof(int) * count);
	if (!original)
		return (ft_putstr_fd("Error\nMemory alloc <alloc_array>\n", 2), NULL);
	i = 0;
	while (i < count)
	{
		if (!is_valid_number(*values))
		{
			ft_putstr_fd("Error\nInvalid input <alloc_array>\n", 2);
			return (free(original), NULL);
		}
		n = ft_atoi(values[i]);
		if (n < INT_MIN || n > INT_MAX)
		{
			ft_putstr_fd("Error\nOut of range <alloc_array>\n", 2);
			return (free(original), NULL);
		}
		original[i++] = (int)n;
	}
	return (original);
}

/*
--> criar uma cópia *sorted;
--> ordenar a cópia;
--> verificar se tem algum numero duplicado;
--> verificando se ja esta ordenado;
*/
int	*duplicate_and_sort(int *original, int count)
{
	int	*sorted;
	int	i;

	sorted = malloc(sizeof(int) * count);
	if (!sorted)
	{
		ft_putstr_fd("Error\nmalloc sorted <duplicate_and-sort>\n", 2);
		return (NULL);
	}
	ft_memcpy(sorted, original, (sizeof(int) * count));
	sort_array(sorted, count);
	i = -1;
	while (++i < count - 1)
	{
		if (sorted[i] == sorted[i + 1])
			return (free(sorted), NULL);
	}
	return (sorted);
}

/*
--> descobre a posição do primeiro número e armazena como index
--> new->value - define o valor da entrada
--> new->index - coloca o index no numero conforme encontrado no sorted
--> if (!*a) - significa que se for o primeiro valor, ...
...ele apenas acrescenta sem fazer loop até o final
--> else - faz o loop até achar a posição final e armazenar o new
(necessário para o t_stack não ficar na ordem inversa da entrada)
*/
void	fill_stack(t_stack **a, int *original, int *sorted, int count)
{
	t_stack	*new;
	t_stack	*tmp;
	int		i;
	int		index;

	i = -1;
	while (++i < count)
	{
		index = get_index(sorted, count, original[i]);
		new = malloc(sizeof(t_stack));
		if (!new)
			return (free_stack(a));
		new->value = original[i];
		new->index = index;
		new->next = NULL;
		if (!*a)
			*a = new;
		else
		{
			tmp = *a;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

//vamos juntar todas as entradas, para aceitar mesmo que seja 2 "3 4" "5" 13 10
char	*join_args(int ac, char **av)
{
	char	*joined;
	int		i;

	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		if (!av[i] || ft_strlen(av[i]) == 0)
		{
			ft_putstr_fd("Error\nEmpty or invalid argument\n", 2);
			return (free(joined), NULL);
		}
		joined = ft_strjoin_and_free(joined, av[i]);
		joined = ft_strjoin_and_free(joined, " ");
		if (!joined)
			return (NULL);
		i++;
	}
	return (joined);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	if (s1)
		free(s1);
	return (joined);
}
