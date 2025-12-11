/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moon_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:12:38 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:40 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_moon_color(unsigned char *pixel, int map_height,
	t_win_prop **win_prop, int lvl)
{
	int				shade;
	unsigned int	color;

	map_height = (int)((*win_prop)->color_scaler * map_height);
	if (map_height < -8000)
		map_height = -8000;
	if (map_height > 8000)
		map_height = 8000;
	shade = (map_height + 8000) * 255 / 16000;
	color = (0xFF << 24) | (shade << 16) | (shade << 8) | shade;
	if ((*win_prop)->b_down == 1)
		*(unsigned int *)pixel = brighten_color(color, lvl);
	else
		*(unsigned int *)pixel = color;
}
