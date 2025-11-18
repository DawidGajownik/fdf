/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:56:41 by dgajowni          #+#    #+#             */
/*   Updated: 2025/10/14 16:56:42 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_pointer_number(unsigned long nbr)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (nbr >= 16)
		count += ft_printf_pointer_number(nbr / 16);
	count += ft_printf_char(base[nbr % 16]);
	return (count);
}

int	ft_printf_pointer(unsigned long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		return (ft_printf_string("(nil)"));
	count += ft_printf_string("0x");
	return (count += ft_printf_pointer_number(ptr));
}
