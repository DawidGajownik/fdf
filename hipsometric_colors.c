/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hipsometric_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:48:49 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/19 11:48:51 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_0_minus(int map_height, t_map_prop **map_prop)
{
	return (0x00AAAAFF + 256 * 256 * (map_height / 32)
		* (256 / (*map_prop)->low_high_diff)
		+ 256 * (map_height / 32)
		* (256 / (*map_prop)->low_high_diff));
}

unsigned int	color_0_minus_object(int map_height, t_object *object)
{
	return (0x00AAAAFF + 256 * 256 * (map_height / 32)
		+ 256 * (map_height / 32));
}

unsigned int	color_0_300(int map_height)
{
	return (0x00AAFFAA - 256 * 256 * (map_height / 2)
		- 256 * (map_height / 2) - (map_height / 2));
}

unsigned int	color_300_1200(int map_height)
{
	return (0x00156A15 + (map_height - 300) / 4 * (256 * 256));
}

unsigned int	color_1200_plus(int map_height)
{
	float			t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (map_height < 1200)
		map_height = 1200;
	if (map_height > 3100)
		map_height = 3100;
	t = (float)(map_height - 1200) / (1900.0);
	r = 0xF5 + (unsigned int)((0xFF - 0xF5) * t);
	g = 0x6A + (unsigned int)((0xFF - 0x6A) * t);
	b = 0x15 + (unsigned int)((0xFF - 0x15) * t);
	return (r * 256 * 256 + g * 256 + b);
}
