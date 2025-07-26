#include "../includes/pipex.h"

static int	real_str_len_cmd(const char *cmd);
static void	restore_space(char **args);
static char	*alloc_new_cmd(const char *cmd);

char	**split_with_quotes(const char *cmd)
{
	char	*clean_cmd;
	char	**args;

	clean_cmd = alloc_new_cmd(cmd);
	if (!clean_cmd)
		return (NULL);
	args = ft_split(clean_cmd, ' ');
	if (!args)
	{
		free(clean_cmd);
		return (NULL);
	}
	restore_space(args);
	free(clean_cmd);
	return (args);
}

static char	*alloc_new_cmd(const char *cmd)
{
	char	quote;
	char	*new_cmd;
	int		i;
	int		j;

	i = -1;
	j = 0;
	quote = 0;
	new_cmd = malloc(real_str_len_cmd(cmd) + 1);
	if (!new_cmd)
		return (NULL);
	while (cmd[++i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '"') && !quote)
			quote = cmd[i];
		else if (cmd[i] == quote)
			quote = 0;
		else if (cmd[i] == '\\')
			continue ;
		else if (quote && cmd[i] == ' ')
			new_cmd[j++] = 31;
		else
			new_cmd[j++] = cmd[i];
	}
	return (new_cmd[j] = '\0', new_cmd);
}

static int	real_str_len_cmd(const char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"' || cmd[i] == '\\')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	restore_space(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == 31)
				args[i][j] = ' ';
			j++;
		}
		i++;
	}
}

int	has_quotes(const char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}
