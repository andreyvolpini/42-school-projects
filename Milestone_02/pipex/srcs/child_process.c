#include "../includes/pipex.h"

static void	exec_cmd(char *cmd, char **envp);
static char	*choose_path(char *cmd_name, char **envp);
static void	handle_exec_error(char *path, char **args, int needs_free);

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

	if (has_quotes(cmd))
		args = split_with_quotes(cmd);
	else
		args = ft_split(cmd, ' ');
	if (!args || !args[0] || !args[0][0])
	{
		ft_putstr_fd("pipex: empty command\n", 2);
		free_split(args);
		exit(127);
	}
	path = choose_path(args[0], envp);
	if (!path)
	{
		free_split(args);
		exit(127);
	}
	needs_free = !ft_strchr(args[0], '/');
	execve(path, args, envp);
	handle_exec_error(path, args, needs_free);
}

static void	handle_exec_error(char *path, char **args, int needs_free)
{
	perror(args[0]);
	if (needs_free)
		free(path);
	free_split(args);
	close(3);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == EISDIR)
		exit(126);
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
			exit(126);
		}
		return (cmd_name);
	}
	path = find_path(cmd_name, envp);
	if (!path)
	{
		ft_putstr_fd("bash: line 1: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		close(4);
		return (NULL);
	}
	return (path);
}
