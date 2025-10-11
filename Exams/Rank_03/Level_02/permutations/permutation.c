#include "permutation.h"

static size_t	ft_strlen(char *s);
static void 	backtrack(char *s, size_t s_len, char *buf, size_t b_len, int *used);

int	main(int ac, char **av)
{
	char	*s, *buf;
	size_t		s_len;
	int			*used;
	char		tmp;

	if (ac != 2)
		return (1);

	s = av[1];
	s_len = ft_strlen(s);
	if (s_len == 0)
		return (1);

	buf = malloc(s_len + 1);
	used = calloc(s_len, sizeof(int));
	if (!buf || !used)
	{
		if (buf)
			free(buf);
		if (used)
			free(used);
		return (1);
	}

	for (size_t i = 0; i < (s_len - 1); i++)
	{
		for (size_t j = i + 1; j < s_len; j++)
		{
			if (s[i] > s[j])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}

	backtrack(s, s_len, buf, 0, used);
	free(buf);
	free(used);
	return (0);
}

static size_t	ft_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static void backtrack(char *s, size_t s_len, char *buf, size_t b_len, int *used)
{
	if (b_len == s_len)
	{
		buf[b_len] = '\0';
		puts(buf);
		return ;
	}

	for (size_t i = 0; i < s_len; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			buf[b_len] = s[i];
			backtrack(s, s_len, buf, b_len + 1, used);
			used[i] = 0;
		}
	}
}
