#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		line_num = 1;

	fd = open("exemplo.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linha %d: %s", line_num++, line);
		free(line);
	}

	close(fd);
	return (0);
}
