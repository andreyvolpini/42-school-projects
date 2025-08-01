/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 07:09:46 by avolpini          #+#    #+#             */
/*   Updated: 2025/07/03 13:40:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

#include <stdlib.h>

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

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + (stash[i] == '\n') + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*remove_line_from_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i) + 1));
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	return (free(stash), new_stash);
}

static int	read_and_stash(int fd, char *buffer, char **stash)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	*stash = ft_strjoin_and_free(*stash, buffer);
	if (!*stash)
		return (-1);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read_and_stash(fd, buffer, &stash);
		if (bytes_read == -1)
			return (free(stash), stash = NULL, NULL);
	}
	if (!stash || stash[0] == '\0')
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	stash = remove_line_from_stash(stash);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

extern int	g_mallocs;
extern int	g_frees;

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
	{
		perror("Erro ao abrir arquivo");
		return (1);
	}

	while ((line = get_next_line(fd)))
	{
		printf("LINE: %s", line);
		free(line);
	}
}
*/
