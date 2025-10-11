#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

int	ft_popen(const char *file, char const **av, char type)
{
	int		fd[2];
	pid_t	pid;

	if (!file || !av || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fd) < 0)
		return (-1);

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				exit (1);
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
				exit (1);
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, (char *const *)av);
		exit(127);
	}

	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}

	if (type == 'w')
	{
		close(fd[0]);
		return (fd[1]);
	}
	return (1);
}


/*---------- TESTES ----------*/
// #include <stdio.h>
// #include <string.h>

/*---------- TESTE R ----------*/
// int main(void)
// {
// 	int 	fd = ft_popen("ls", (char const*[]){"ls", "-1", NULL}, 'r');;
// 	char	buf[256];
// 	ssize_t n;

// 	if (fd < 0)
// 	{
// 		perror("ft_open r");
// 		return (1);
// 	}

// 	while ((n = read(fd, buf, sizeof buf)) > 0)
// 		write(STDOUT_FILENO, buf, n);

// 	close(fd);
// 	return (0);
// }

/*---------- TESTE W ----------*/
// int main(void)
// {
// 	int	fd = ft_popen("wc", (char const*[]){"wc", "-c", NULL}, 'w');;

// 	const char	*msg = "Hello\n42\n";
// 	int			n = strlen(msg);

// 	if (fd < 0)
// 	{
// 		perror("ft_open w");
// 		return (1);
// 	}

// 	write(fd, msg, n);
// 	close(fd);
// 	return (0);
// }

/*---------- TESTE ERRO ----------*/
// int main(void)
// {
// 	int 	fd = ft_popen("invadi_command", (char const*[]){"invadi_command", NULL}, 'r');;
// 	char	buf[256];
// 	ssize_t n;

// 	if (fd < 0)
// 	{
// 		perror("ft_open w");
// 		return (1);
// 	}

// 	n = read(fd, buf, sizeof buf);
// 	printf("read returned %zd (expected EOF => 0)\n", n);
// 	close(fd);
// 	return (0);
// }
