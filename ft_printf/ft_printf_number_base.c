/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:26:52 by dgajowni          #+#    #+#             */
/*   Updated: 2025/05/26 16:26:52 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_number_base(unsigned int nbr, int base_version)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	if (base_version == 1)
		base = "0123456789ABCDEF";
	count = 0;
	if (nbr >= 16)
		count += ft_printf_number_base(nbr / 16, base_version);
	count += ft_printf_char(base[nbr % 16]);
	return (count);
}
