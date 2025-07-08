#ifndef PARSING_H
# define PARSING_H

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

//parsing_utils.c
int		is_valid_number(const char *str);
void	sort_array(int *original, int count);
int		is_sorted(int *original, int *sorted, int count);
int		get_index(int *sorted, int count, int value);
void	free_stack(t_stack **stack);

//parsing.c
int		*alloc_array(int count, char **values);
int		*duplicate_and_sort(int *original, int count);
void	fill_stack(t_stack **a, int *original, int *sorted, int count);
char	*join_args(int ac, char **av);
char	*ft_strjoin_and_free(char *s1, char *s2);

#endif