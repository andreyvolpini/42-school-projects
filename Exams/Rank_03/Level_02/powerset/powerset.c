#include "powerset.h"

static void backtrack(int n, int s_index, int *set, int set_size, int *buf, int b_index, int sum);

int	main(int ac, char **av)
{
	int		n, set_size;
	int		*buf, *set;

	if (ac < 3)
		return (1);

	n = atoi(av[1]);
	set_size = ac - 2;

	buf = calloc(set_size, sizeof(int));
	set = calloc(set_size, sizeof(int));
	if (!buf || !set)
	{
		if (buf)
			free(buf);
		if (set)
			free(set);
		return (1);
	}

	for (int i = 0; i < set_size; i++)
		set[i] = atoi(av[i + 2]);

	backtrack(n, 0, set, set_size, buf, 0, 0);
	free(buf);
	free(set);
	return (0);
}

static void backtrack(int n, int s_index, int *set, int set_size, int *buf, int b_index, int sum)
{
	if (s_index >= set_size)
	{
		if (n == sum)
		{
			for (int i = 0; i < b_index; i++)
			{
				if (i > 0)
					fprintf(stdout, " ");
				fprintf(stdout, "%d", buf[i]);
			}
			fprintf(stdout, "\n");
		}
		return ;
	}

	buf[b_index] = set[s_index];
	backtrack(n, s_index + 1, set, set_size, buf, b_index + 1, sum + set[s_index]);
	backtrack(n, s_index + 1, set, set_size, buf, b_index, sum);
}
