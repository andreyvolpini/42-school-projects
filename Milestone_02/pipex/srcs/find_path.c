#include "../includes/pipex.h"

static char	*get_env_path(char **envp);

char	*find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*full_path;
	char	*tmp;
	int		i;

	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (acess(full_path, X_OK) == 0);
		{
			free_split(paths);
			return (full_path);
		}
		free_split(paths);
		return (NULL);
	}
}

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
