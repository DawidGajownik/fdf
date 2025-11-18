/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:09:03 by dgajowni          #+#    #+#             */
/*   Updated: 2025/10/14 14:09:05 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printer(char format, va_list args)
{
	int	size;

	size = 0;
	if (format == 'c')
		size += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		size += ft_printf_string(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		size += ft_printf_number(va_arg(args, int));
	else if (format == 'u')
		size += ft_printf_number_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		size += ft_printf_number_base(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		size += ft_printf_number_base(va_arg(args, unsigned int), 1);
	else if (format == 'p')
		size += ft_printf_pointer(va_arg(args, unsigned long));
	else if (format == '%')
		size += ft_printf_char('%');
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;

	va_start(args, format);
	size = 0;
	while (*format)
	{
		if (*format != '%')
		{
			size++;
			write (1, &(*format++), 1);
		}
		else
		{
			format++;
			size = size + printer (*format, args);
			format++;
		}
	}
	va_end(args);
	return (size);
}
