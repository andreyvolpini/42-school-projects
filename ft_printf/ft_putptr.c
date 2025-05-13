#include "ft_printf.h"

static int	put_hex_ptr(unsigned long n)
{
	char	*base;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		len += put_hex_ptr(n / 16);
	len += ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putptr(unsigned long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	len += write(1, "0x", 2);
	len += put_hex_ptr(ptr);
	return (len);
}
