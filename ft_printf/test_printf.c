#include <stdio.h>
#include "ft_printf.h"

int	main(void)
{
	int	len1, len2;
	char *str = "Hello";
	int	num = -42;
	unsigned int u = 123456;
	void *ptr = &num;

	printf("===== TESTES ft_printf =====\n\n");

	len1 = ft_printf("ft_printf: Char: [%c]\n", 'A');
	len2 = printf   ("printf   : Char: [%c]\n", 'A');
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Str: [%s]\n", str);
	len2 = printf   ("printf   : Str: [%s]\n", str);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Int d: [%d]\n", num);
	len2 = printf   ("printf   : Int d: [%d]\n", num);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Int i: [%i]\n", num);
	len2 = printf   ("printf   : Int i: [%i]\n", num);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Unsigned: [%u]\n", u);
	len2 = printf   ("printf   : Unsigned: [%u]\n", u);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Hex x: [%x]\n", u);
	len2 = printf   ("printf   : Hex x: [%x]\n", u);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Hex X: [%X]\n", u);
	len2 = printf   ("printf   : Hex X: [%X]\n", u);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Ptr: [%p]\n", ptr);
	len2 = printf   ("printf   : Ptr: [%p]\n", ptr);
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	len1 = ft_printf("ft_printf: Percent: [%%]\n");
	len2 = printf   ("printf   : Percent: [%%]\n");
	printf("Retornos: ft = %d | libc = %d\n\n", len1, len2);

	return (0);
}
