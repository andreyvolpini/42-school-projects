#include "../includes/pipex.h"
#include <sys/wait.h>

static pid_t	spawn_child1(int infile, int pipefd[2], char *cmd, char **envp);
static pid_t	spawn_child2(int oufile, int pipefd[2], char *cmd, char **envp);
static void		setup_fds(int ac, char **av, int *infile, int *outfile);

int	main(int ac, char **av, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	setup_fds(ac, av, &infile, &outfile);
	if (pipe(pipefd) < 0)
		perror_exit("pipe");
	pid1 = spawn_child1(infile, pipefd, av[2], envp);
	pid2 = spawn_child2(outfile, pipefd, av[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

static pid_t	spawn_child1(int infile, int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("Error: fork failed\n", 2), -1);
	if (pid == 0)
		child_process1(infile, pipefd, cmd, envp);
	return (pid);
}

static pid_t	spawn_child2(int oufile, int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("Error: fork failed\n", 2), -1);
	if (pid == 0)
		child_process2(oufile, pipefd, cmd, envp);
	return (pid);
}

static void	setup_fds(int ac, char **av, int *infile, int *outfile)
{
	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	*infile = open(av[1], O_RDONLY);
	if (*infile < 0)
		perror_exit(av[1]);
	*outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
		perror_exit(av[4]);
}
