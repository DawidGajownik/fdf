/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:33:29 by dgajowni          #+#    #+#             */
/*   Updated: 2025/09/28 18:33:30 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	set_result(const char *str)
{
	int	result;
	int	minus;

	result = 0;
	minus = 1;
	if (*str && *str == '+')
		str++;
	else if (*str && *str == '-')
	{
		minus = (-1);
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + ((*str) - 48);
		str++;
	}
	return (result * minus);
}

int	ft_atoi(const char *nptr)
{
	while (*nptr)
	{
		if (*nptr == ' ' || (*nptr > 8 && *nptr < 14))
			nptr++;
		else if (*nptr == '+' || *nptr == '-' || (*nptr >= '0' && *nptr <= '9'))
			return (set_result(nptr));
		else
			return (0);
	}
	return (0);
}
