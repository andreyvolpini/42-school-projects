#include "rip.h"

static void backtrack(char *s, int index, int left, int right, int open, char *buf);
static int	is_valid(char *s);

int	main(int ac, char **av)
{
	char	*s, *buf;
	int		i = 0, left = 0, right = 0;

	if (ac != 2)
		return (1);

	s = av[1];

	while (s[i])
	{
		if (s[i] == '(')
			left++;
		else
		{
			if (left > 0)
				left--;
			else
				right++;
		}
		i++;
	}

	buf = malloc(i + 1);
	if (!buf)
		return (1);

	backtrack(s, 0, left, right, 0, buf);
	free(buf);
	return (0);
}

static void backtrack(char *s, int index, int left, int right, int open, char *buf)
{
	if (s[index] == '\0')
	{
		buf[index] = '\0';
		if (is_valid(buf))
			puts(buf);
		return ;
	}

	else if (s[index] == '(')
	{
		if (left > 0)
		{
			buf[index] = ' ';
			backtrack(s, index + 1, left - 1, right, open, buf);
		}
		buf[index] = '(';
		backtrack(s, index + 1, left, right, open + 1, buf);
	}

	else
	{
		if (right > 0)
		{
			buf[index] = ' ';
			backtrack(s, index + 1, left, right - 1, open, buf);
		}
		if (open > 0)
		{
			buf[index] = ')';
			backtrack(s, index + 1, left, right, open - 1, buf);
		}
	}
}

static int	is_valid(char *s)
{
	int	count = 0;

	while (*s)
	{
		if (*s == '(')
			count++;
		else if (*s == ')')
		{	if (count == 0)
				return (0);
			count--;
		}
		s++;
	}
	return (count == 0);
}
