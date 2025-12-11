/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:06:30 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:06:32 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

unsigned int	ft_atoi_hex(const char *str)
{
	unsigned int	result;
	int				i;
	char			c;
	unsigned int	value;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			value = c - '0';
		else if (c >= 'a' && c <= 'f')
			value = 10 + (c - 'a');
		else if (c >= 'A' && c <= 'F')
			value = 10 + (c - 'A');
		else
			break ;
		result = result * 16 + value;
		i++;
	}
	return (result);
}
