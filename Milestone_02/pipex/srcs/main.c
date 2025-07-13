#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		return (ft_putstr_fd("Error: cannot open infile\n", 2), 1);

	outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile < 0)
		return (ft_putstr_fd("Error: cannot open/create outfile\n", 2), 1);
	
	if (pipe(pipefd) < 0)
		return (ft_putstr_fd("Error: pipe failed", 2), 1);

	pid1 = fork();
	if (pid1 < 0)
		return (ft_putstr_fd("Error: fork failed", 2), 1);
	if (pid1 == 0)
		child_process1(infile, pipefd, av[2], envp);

	pid2 = fork();
	if (pid2 < 0)
		return (ft_putstr_fd("Error: fork failed", 2), 1);
	if (pid2 == 0)
		child_process2(infile, pipefd, av[3], envp);

	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
