<h1 align="center"> Passo a passo para implementar o Push_Swap</h1>

<p align="left">
  O programa recebe uma sequência de inteiros sem repetição pela linha de comando. O objetivo é ordenar A em ordem crescente, minimizando o número de movimentos.
  
  Deve usar duas pilhas (A e B) e as operações:
  	<strong>sa, sb, ss (swap topo de A/B)
	pa, pb (push entre pilhas)
	ra, rb, rr (rotate para cima)
	rra, rrb, rrr (rotate para baixo)</strong>

</p>

## main.c
```bash
int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		*original;
	int		*sorted;
	char	**values;

	(void)av;
	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
	if (!parse_args(&values, ac, av))
		return (1);
	if (!setup_stacks(&a, &values, &original, &sorted))
		return (1);
	to_choose(&a, &b, count_values(values));
	free_stack(&a);
	free_stack(&b);
	free(original);
	free(sorted);
	free_split(values);
	return (0);
}
```
### Primeiro vamos declarar as variáveis
```bash
int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	int		*original;
	int		*sorted;
	char	**values;

	(void)av;
	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
...
```
- t_stack *a, *b; → ponteiros para as suas duas pilhas (A e B).

- int *original, *sorted; → vetores de inteiros, onde vou guardar uma guarda a sequência de entrada e uma cópia ordenada.

- char **values; → array de strings (os argumentos já filtrados e validados).

a = NULL; e b = NULL; para garantir que se algo der errado antes de alocar, os frees não deem segfault.

if (ac < 2) programa só roda se tiver pelo menos um argumento alem do ./push_swap.


### Vamos verificar se o parse_args é válido
```bash
	if (!parse_args(&values, ac, av))
		return (1);
```
```bash
int	parse_args(char	***v, int ac, char **av)
{
	char	*joined;

	joined = join_args(ac, av);
	if (!joined)
		return (ft_putstr_fd("Error\nMemory alloc <join_args>\n", 2), 0);
	*v = ft_split(joined, ' ');
	free(joined);
	if (!*v || !**v || count_values(*v) == 0)
		return (ft_putstr_fd("Error\nSplit failed\n", 2), free_split(*v), 0);
	return (1);
}
```


- 📁 [`push_swap`](./push_swap)
---
## 🚀 Cloning the Repository

```bash
git clone https://github.com/andreyvolpini/42-school-projects/push_swap.git
cd push_swap

