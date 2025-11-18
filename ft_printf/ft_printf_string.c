/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:02:52 by dgajowni          #+#    #+#             */
/*   Updated: 2025/10/02 15:02:53 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_string(char *s)
{
	int	i;

	if (s == NULL)
		return (ft_printf_string("(null)"));
	i = 0;
	while (*s)
	{
		ft_printf_char(*s);
		s++;
		i++;
	}
	return (i);
}
