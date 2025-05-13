#include "ft_printf.h"

int	ft_putstr( char *str)
{
	int	len;

	if (!str)
		return (write(1, "(null)", 6));
	len = 0;
	while (str[len])
		write(1, &str[len++], 1);
	return (len);
}
