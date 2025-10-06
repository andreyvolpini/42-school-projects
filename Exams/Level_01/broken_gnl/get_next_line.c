#include "get_next_line.h"

static void *ft_memchr(const void *src, int c, size_t n);
static void *ft_memcpy(void *dst, const void *src, size_t n);
static void *ft_memmove(void *dst, const void *src, size_t n);
static int	append_bt(unsigned char **stash, size_t *len, const unsigned char *buf, size_t n);
static char	*extract_line(unsigned char **stash, size_t *len);
static void	cleanup(unsigned char **stash, size_t *len);

char	*get_next_line(int fd)
{
	static unsigned char	*stash;
	static size_t			len;
	unsigned char			*pos_nl;
	unsigned char			buf[BUFFER_SIZE];
	ssize_t					b_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	pos_nl = ft_memchr(stash, '\n', len);
	if (len && pos_nl)
		return (extract_line(&stash, &len));
	
	while (1)
	{
		b_read = read(fd, buf, BUFFER_SIZE);

		if (b_read < 0)
		{
			cleanup(&stash, &len);
			return (NULL);
		}

		if (b_read == 0)
		{
			if (len == 0)
				return (NULL);
			return (extract_line(&stash, &len));
		}

		if (!append_bt(&stash, &len, buf, (size_t)b_read))
		{
			cleanup(&stash, &len);
			return (NULL);
		}

		pos_nl = ft_memchr(stash, '\n', len);
		if (pos_nl)
			return (extract_line(&stash, &len));
	}
}

static void *ft_memchr(const void *src, int c, size_t n)
{
	const unsigned char *s = (const unsigned char *)src;
	unsigned char		uc = (unsigned char)c;

	for (size_t i = 0; i < n; i++)
	{
		if (s[i] == uc)
			return ((void *)(s + i));
	}
	return (NULL);
}

static void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char 		*d = (unsigned char *)dst;
	const unsigned char *s = (const unsigned char *)src;

	for (size_t i = 0; i < n; i++)
		d[i] = s[i];
	return (dst);
}

static void *ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char 		*d = (unsigned char *)dst;
	const unsigned char *s = (const unsigned char *)src;

	if (d < s)
	{
		for (size_t i = 0; i < n; i++)
			d[i] = s[i];
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dst);
}

static int	append_bt(unsigned char **stash, size_t *len, const unsigned char *buf, size_t n)
{
	unsigned char	*tmp;

	if (*len > (SIZE_MAX - n))
		return (0);

	tmp = realloc(*stash, *len + n);
	if (!tmp)
		return (0);

	ft_memcpy(tmp + *len, buf, n);
	*stash = tmp;
	*len += n;

	return (1);
}

static char	*extract_line(unsigned char **stash, size_t *len)
{
	unsigned char	*pos_nl;
	size_t			size_nl;
	char			*line;

	pos_nl = (unsigned char *)ft_memchr(*stash, '\n', *len);
	if (pos_nl)
		size_nl = (size_t)(pos_nl - *stash) + 1;
	else
		size_nl = *len;

	line = malloc(size_nl + 1);
	if (!line)
		return (NULL);

	ft_memcpy(line, *stash, size_nl);
	line[size_nl] = '\0';

	if (size_nl == *len)
		cleanup(stash, len);
	else
	{
		ft_memmove(*stash, *stash + size_nl, *len - size_nl);
		*len -= size_nl;
	}
	return (line);
}

static void	cleanup(unsigned char **stash, size_t *len)
{
	free(*stash);
	*stash = NULL;
	*len = 0;
}
/*
int	main(void)
{
	int		fd = open("get_next_line.c", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/

