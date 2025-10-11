#include "n_queens.h"

static int	is_safe(int *board, int col, int row);
void		backtrack(int *board, int col, int n);

int main(int ac, char **av)
{
	int	*board;
	int		n;

	if (ac != 2)
		return (1);

	n = atoi(av[1]);
	board = calloc(n, sizeof(int));
	if (!board)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (1);
	}

	backtrack(board, 0, n);
	free(board);
	return (0);
}

void	backtrack(int *board, int col, int n)
{
	if (col == n)
	{
		for (int i = 0; i < n; i++)
		{
			if (i > 0)
				fprintf(stdout, " ");
			fprintf(stdout, "%d", board[i]);
		}
		fprintf(stdout, "\n");
		return ;
	}

	for (int row = 0; row < n; row++)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			backtrack(board, col + 1, n);
		}
	}
}

static int	is_safe(int *board, int col, int row)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
			return (0);

		if (abs(board[i] - row) == abs(i - col))
			return (0);
	}
	return (1);
}
