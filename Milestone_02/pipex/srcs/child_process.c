#include "../includes/pipex.h"

void	exc_cmd(char *cmd, char **envp);

void	child_process1(int infile, int pipefd[2], char *cmd, char **envp)
{
	if (dup2(infile, 0) < 0)
		return (ft_putstr_fd("Error: dup2 infile failed", 2));

	if (dup2(infile, 1) < 0)
		return (ft_putstr_fd("Error: dup2 pipe write and failed", 2));

	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);

	exec_cmd(cmd, envp);
	return (ft_putstr_fd("Error: execve cdm1 failed", 2));
}

void	exc_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		return (ft_putstr_fd("Error: ft_split failed", 2));

	path = find_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		free_split(args);
		exit(127);
	}

	execve(path, args, envp);

	free(path);
	free_split(args);
	return (ft_putstr_fd("Error: execve failed", 2));
}
