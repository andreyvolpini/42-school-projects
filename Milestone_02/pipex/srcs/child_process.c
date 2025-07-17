#include "../includes/pipex.h"

void		perror_exit(const char *msg);
static void	exec_cmd(char *cmd, char **envp);
static char	*choose_path(char *cmd_name, char **envp);

void	child_process1(int infile, int pipefd[2], char *cmd, char **envp)
{
	if (dup2(infile, 0) < 0)
		perror_exit("dup2 infile");
	if (dup2(pipefd[1], 1) < 0)
		perror_exit("dup2 pipe write");
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	exec_cmd(cmd, envp);
	perror("execve cmd1");
	exit(EXIT_FAILURE);
}

void	child_process2(int outfile, int pipefd[2], char *cmd, char **envp)
{
	if (dup2(pipefd[0], 0) < 0)
		perror_exit("dup2 pipe read");
	if (dup2(outfile, 1) < 0)
		perror_exit("dup2 outfile");
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	exec_cmd(cmd, envp);
	perror("execve cmd2");
	exit(EXIT_FAILURE);
}

static void	exec_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	int		needs_free;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_putstr_fd("Error: ft_split failed", 2);
		exit(EXIT_FAILURE);
	}
	path = choose_path(args[0], envp);
	needs_free = !ft_strchr(args[0], '/');
	execve(path, args, envp);
	if (needs_free)
		free(path);
	free_split(args);
	if (errno == ENOENT)
		exit(127);
	else
		exit(EXIT_FAILURE);
}

static char	*choose_path(char *cmd_name, char **envp)
{
	char	*path;

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, X_OK) < 0)
		{
			perror(cmd_name);
			exit(127);
		}
		return (cmd_name);
	}
	path = find_path(cmd_name, envp);
	if (!path)
	{
		ft_putstr_fd("bash: line 1: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (path);
}

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
