#define _GNU_SOURCE
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static size_t	ft_strlen_nullsafe(const char *s);

int	main(int ac, char **av)
{
	char	*s = av[1];
	size_t	len = ft_strlen_nullsafe(s);
	ssize_t	b_read;
	size_t	t_read = 0;
	char	*buf, *tmp, *cursor, *end, *match;

	if (ac != 2 || BUFFER_SIZE <= 0 || len == 0)
		return (1);

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		perror("Error");
		return (1);
	}

	while (1)
	{
		b_read = read(0, buf + t_read, BUFFER_SIZE);

		if (b_read < 0)
		{
			perror("Error");
			free(buf);
			return (1);
		}

		if (b_read == 0)
			break ;

		t_read += (size_t)b_read;
		buf[t_read] = '\0';

		if (t_read > (SIZE_MAX - (size_t)BUFFER_SIZE + 1))
		{
			fprintf(stderr, "Input too large\n");
			free(buf);
			return (1);
		}

		tmp = realloc(buf, BUFFER_SIZE + t_read);
		if (!tmp)
		{
			perror("Error");
			free(buf);
			return (1);
		}
		buf = tmp;		
	}

	cursor = buf;
	end = buf + t_read;
	while (cursor < end)
	{
		match = memmem(cursor, end - cursor, s, len);
		if (!match)
		{
			write(1, cursor, end - cursor);
			break ;
		}
		write(1, cursor, match - cursor);
		for (size_t i = 0; i < len; i++)
			write(1, "*", 1);

		cursor = match + len;
	}

	free(buf);
	return (0);
}

static size_t	ft_strlen_nullsafe(const char *s)
{
	size_t	i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

