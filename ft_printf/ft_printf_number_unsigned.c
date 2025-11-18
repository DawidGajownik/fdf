/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_unsigned.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:10:25 by dgajowni          #+#    #+#             */
/*   Updated: 2025/10/02 15:10:26 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_number_unsigned(unsigned int nbr)
{
	unsigned int	count;

	count = 0;
	if (nbr >= 10)
		count += ft_printf_number_unsigned(nbr / 10);
	count += ft_printf_char((nbr % 10) + 48);
	return (count);
}
