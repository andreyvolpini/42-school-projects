#include "ft_printf.h"

int	ft_putnbr_hex(unsigned int n, char format)
{
        char	*base;
	int	len;

	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 0;
	if (n >= 16)
		len += ft_putnbr_hex(n / 16, format);
	len += ft_putchar(base[n % 16]);
	return (len);

}