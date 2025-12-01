/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hipcometric_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:23:26 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:23:27 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int brighten_color(unsigned int color, int amount)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;

	r = r + amount; if (r > 255) r = 255;
	g = g + amount; if (g > 255) g = 255;
	b = b + amount; if (b > 255) b = 255;

	return (r << 16) | (g << 8) | b;
}

void	set_hipsometric_color_object(unsigned char *pixel, int map_height,
	t_object *object, t_win_prop **win_prop)
{
	if (map_height <= 0)
		*(unsigned int *)pixel = color_0_minus_object(map_height, object);
	else if (map_height < 300)
		*(unsigned int *)pixel = color_0_300(map_height);
	else if (map_height < 1200)
		*(unsigned int *)pixel = color_300_1200(map_height);
	else
		*(unsigned int *)pixel = color_1200_plus(map_height);
}

void	set_hipsometric_color_brighter(unsigned char *pixel, int map_height,
	t_map_prop **map_prop, t_win_prop **win_prop)
{
	map_height = (int)((*win_prop)->color_scaler * map_height);
	if (map_height <= 0)
		*(unsigned int *)pixel = brighten_color(color_0_minus(map_height, map_prop), 40);
	else if (map_height < 300)
		*(unsigned int *)pixel = brighten_color(color_0_300(map_height), 40);
	else if (map_height < 1200)
		*(unsigned int *)pixel = brighten_color(color_300_1200(map_height), 40);
	else
		*(unsigned int *)pixel = brighten_color(color_1200_plus(map_height), 40);
}

void	set_hipsometric_color(unsigned char *pixel, int map_height,
	t_map_prop **map_prop, t_win_prop **win_prop)
{
	*(unsigned int *)pixel = map_height;
	/*map_height = (int)((*win_prop)->color_scaler * map_height);
	if (map_height <= 0)
		*(unsigned int *)pixel = color_0_minus(map_height, map_prop);
	else if (map_height < 300)
		*(unsigned int *)pixel = color_0_300(map_height);
	else if (map_height < 1200)
		*(unsigned int *)pixel = color_300_1200(map_height);
	else
		*(unsigned int *)pixel = color_1200_plus(map_height);*/
}
