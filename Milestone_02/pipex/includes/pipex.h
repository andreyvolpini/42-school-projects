#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

void	child_process1(int infile, int pipefd[2], char *cmd, char **envp);
void	child_process2(int outfile, int pipefd[2], char *cmd, char **envp);

char	*find_path(char *cmd, char **envp);
void	perror_exit(const char *msg);

#endif