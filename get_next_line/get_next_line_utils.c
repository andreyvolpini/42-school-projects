#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	size_t		s_len;
	char		*array;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	array = malloc(sizeof(char) * (s_len + 1));
	if (!array)
		return (0);
	i = 0;
	while (s[i])
	{
		array[i] = s[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			i;
	size_t			j;
	char			*joined;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (0);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[j + i] = s2 [j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*substring;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substring = malloc(1);
		if (!substring)
			return (0);
		substring[0] = '\0';
		return (substring);
	}
	if (len > (s_len - start))
		len = s_len - start;
	substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (0);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[len] = '\0';
	return (substring);
}

char	*extract_line(char *stash)
{
	size_t		i;
	char		*line;

	if (!stash || stash[0] == '\0')
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

char	*remove_line_from_stash(char *stash)
{
	size_t		i;
	size_t		j;
	char		*new_stash;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (0);
	}
	i++;
	new_stash = malloc(ft_strlen(stash + i) + 1);
	if (!new_stash)
		return (0);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
