#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define FAILED -1
#define NO_EXIST -1

static int	count_cmds(char **cmds)
{
	int	i = 0, n = 0;

	if (!cmds)
		return (0);
	while (1)
	{
		if (cmds[i] == NULL)
		{
			if (i == 0)
				return (0);
			n++;
			if (cmds[i + 1] == NULL)
				break ;
			i++;
		}
		else	i++;
	}
	return (n);
}

int picoshell(char *cmds[])
{
	int		n_cmds	= count_cmds(cmds);
	char	**av;
	int		idx 	= 0;
	int		prev_in = -1;
	int		last;
	int		fd[2];
	int		status;
	int		ret = 0;
	pid_t	pid;

	if (n_cmds == 0)
		return (1);
	
	for (int i = 0; i < n_cmds; i++) // Position
	{
		av = &cmds[idx];
		if (av[0] == NULL)
		{
			if (prev_in != -1)
				close(prev_in);
			return (1);
		}

		while (cmds[idx] != NULL)
			idx++;
		idx++;

		last = (i == (n_cmds - 1));
		if (!last)
		{
			if (pipe(fd) == FAILED)
			{
				if (prev_in != NO_EXIST)
					close(prev_in);
				return (1);
			}
		}

		pid = fork();
		if (pid < 0) // Error
		{
			if (!last)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (prev_in != NO_EXIST)
				close(prev_in);
			return (1);
		}

		if (pid == 0) // Child
		{
			if (prev_in != NO_EXIST)
			{
				if (dup2(prev_in, 0) == FAILED)
				{
					if (!last)
					{
						close(fd[0]);
						close(fd[1]);
					}
					if (prev_in != NO_EXIST)
						close(prev_in);
					return (1);
				}
			}
			
			if (!last)
			{
				if (dup2(fd[1], 1) == FAILED)
				{
					if (!last)
					{
						close(fd[0]);
						close(fd[1]);
					}
					if (prev_in != -1)
						close(prev_in);
					exit(1);
				}
			}

			if (!last)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (prev_in != NO_EXIST)
				close(prev_in);
			
			execvp(av[0], av);
			exit(1);
		}
		else // Father
		{
			if (prev_in != NO_EXIST)
				close(prev_in);
			if (!last)
			{
				close(fd[1]);
				prev_in = fd[0];
			}

		}
	}
	
	if (prev_in != NO_EXIST)
	close(prev_in);
	
	for (int k = 0; k < n_cmds, k++)
	{
		if (wait(&status) == FAILED)
			return (1);

		if (!WIFEXITED(status) || WIFEXITED(status) != 0)
			ret = 1;
	}
	return (ret);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*cmds[] = {"ls", NULL,
						"grep", "picoshell", NULL,
						"wc", "-c", NULL,
						NULL};

	if (picoshell(cmds) != 0)
	{
		perror("picoshell failed");
		return (1);
	}
	return (0);
}
*/
