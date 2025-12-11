/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:06:52 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:06:55 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_putint(char *ptr, int n)
{
	int	len;
	int	tmp;

	tmp = n;
	len = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	ptr[len] = '\0';
	while (len--)
	{
		ptr[len] = (n % 10) + '0';
		n /= 10;
	}
}

static char	*ft_putfrac(char *ptr, float frac, int precision)
{
	int	i;
	int	digit;

	i = 0;
	while (i < precision)
	{
		frac *= 10;
		digit = (int)frac;
		*ptr++ = digit + '0';
		frac -= digit;
		i++;
	}
	*ptr = '\0';
	return (ptr);
}

char	*ft_ftoa(float n, int precision)
{
	char	*str[2];
	int		int_part;
	float	frac_part;

	str[0] = malloc(50);
	if (!str)
		return (NULL);
	str[1] = str[0];
	int_part = (int)n;
	frac_part = n - int_part;
	if (n < 0)
	{
		*str[1]++ = '-';
		int_part = -int_part;
		frac_part = -frac_part;
	}
	ft_putint(str[1], int_part);
	while (*str[1])
		str[1]++;
	if (precision > 0)
	{
		*str[1]++ = '.';
		ft_putfrac(str[1], frac_part, precision);
	}
	return (str[0]);
}
