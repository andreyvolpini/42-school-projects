#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	char	*line;
	int	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	line = extract_line(stash);
	stash = remove_line_from_stash(stash);
	return (line);
}
