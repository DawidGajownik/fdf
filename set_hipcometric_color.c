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

void	set_hipsometric_color(unsigned char *pixel, int map_height,
	t_map_prop **map_prop, t_win_prop **win_prop)
{
	if (map_height <= 0)
		*(unsigned int *)pixel = color_0_minus(map_height, map_prop);
	else if (map_height < 300)
		*(unsigned int *)pixel = color_0_300(map_height);
	else if (map_height < 1200)
		*(unsigned int *)pixel = color_300_1200(map_height);
	else
		*(unsigned int *)pixel = color_1200_plus(map_height);
}
