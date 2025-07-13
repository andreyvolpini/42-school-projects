#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

void	exc_cmd(char *cmd, char **envp);
void	child_process1(int infile, int pipefd[2], char *cmd, char **envp);

char	*find_path(char *cmd, char **envp);

#endif