#include <fcntl.h>      // open
#include <stdio.h>      // printf
#include <stdlib.h>     // free
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("1char.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}

	line = get_next_line(fd);
	if (line)
	{
		if (line[0] == 'a' && line[1] == '\0')
			printf("✅ get_next_line: Leitura correta de 1char.txt: \"%s\"\n", line);
		else
			printf("❌ Erro: conteúdo incorreto: \"%s\"\n", line);
		free(line);
	}
	else
		printf("❌ Erro: linha NULL (esperado \"a\")\n");

	line = get_next_line(fd);
	if (!line)
		printf("✅ Fim do arquivo corretamente detectado (NULL)\n");
	else
	{
		printf("❌ Erro: deveria retornar NULL, mas retornou: \"%s\"\n", line);
		free(line);
	}

	close(fd);
	return (0);
}
