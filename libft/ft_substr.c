#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
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
	ft_memcpy(substring, s + start, len);
	substring[len] = '\0';
	return (substring);
}
