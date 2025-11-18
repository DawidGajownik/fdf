/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:10:25 by dgajowni          #+#    #+#             */
/*   Updated: 2025/10/02 15:10:26 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_number(int nbr)
{
	int	count;

	count = 0;
	if (nbr == -2147483648)
		return (ft_printf_string("-2147483648"));
	if (nbr < 0)
	{
		count += ft_printf_char('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		count += ft_printf_number(nbr / 10);
	count += ft_printf_char((nbr % 10) + 48);
	return (count);
}
