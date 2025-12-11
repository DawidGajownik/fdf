/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:08:44 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:45 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	distance(t_vec2 a, t_vec2 b)
{
	return (sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

void	get_coords_from_addr(unsigned char *addr, t_map_prop **map_prop,
		t_win_prop **win_prop, t_vec2 *p)
{
	long	offset;
	int		row;
	int		col;

	offset = addr - (*map_prop)->img_data;
	row = offset / (*map_prop)->line_size;
	col = (offset % (*map_prop)->line_size) / (*map_prop)->bytes_pp;
	(*p).y = ((*win_prop)->height / 2) - row;
	(*p).x = col - ((*win_prop)->width / 2);
}

static void	set_color(t_map_prop **map_prop, t_win_prop **win_prop,
		unsigned char *pixel, int map_height)
{
	int	lvl;

	lvl = 0;
	if ((*win_prop)->b_down == 1)
		lvl = 40;
	if ((*win_prop)->c_down == 0 && (*win_prop)->z_down == 0)
		set_color_blue(pixel, map_height, win_prop, lvl);
	if ((*win_prop)->c_down == 1 && (*win_prop)->z_down == 0)
		set_color_green(pixel, map_height, win_prop, lvl);
	if ((*win_prop)->c_down == 2 && (*win_prop)->z_down == 0)
		set_color_red(pixel, map_height, win_prop, lvl);
	if ((*win_prop)->c_down == 4 && (*win_prop)->z_down == 0)
		set_moon_color(pixel, map_height, win_prop, lvl);
	if ((*win_prop)->c_down == 3 && (*win_prop)->z_down == 0)
	{
		if ((*win_prop)->b_down == 1)
			set_hipsometric_color_brighter(pixel, map_height,
				map_prop, win_prop);
		else
			set_hipsometric_color(pixel, map_height, map_prop, win_prop);
	}
	if ((*win_prop)->z_down == 1)
		*(unsigned int *)pixel = map_height;
}

void	paint_point(t_map_prop **map_prop, t_win_prop **win_prop,
		int map_height, t_vec2 p)
{
	unsigned char	*pixel;
	int				half_x;
	int				half_y;

	half_x = (*win_prop)->width / 2;
	half_y = (*win_prop)->height / 2;
	if (p.x <= -half_x + 1 || p.x >= half_x - 10
		|| p.y <= -half_y || p.y >= half_y)
		return (NULL);
	pixel = ((*map_prop)->img_data
			+ (((*win_prop)->height / 2 - (p.y)) * (*map_prop)->line_size)
			+ (((p.x) + (*win_prop)->width / 2) * (*map_prop)->bytes_pp));
	set_color(map_prop, win_prop, pixel, map_height);
}

int	point_in_poly(int x, int y, t_vec2 poly[4])
{
	int		inside;
	t_vec2	ii;
	t_vec2	jj;
	t_vec2	inc;
	int		intersect;

	inside = 0;
	inc.x = 0;
	inc.y = 3;
	while (inc.x < 4)
	{
		ii.x = poly[inc.x].x;
		ii.y = poly[inc.x].y;
		jj.x = poly[inc.y].x;
		jj.y = poly[inc.y].y;
		intersect = ((ii.y > y) != (jj.y > y)) && (x < (jj.x - ii.x)
				* (float)(y - ii.y) / (float)(jj.y - ii.y + 0.00001f) + ii.x);
		if (intersect)
			inside = !inside;
		inc.y = inc.x++;
	}
	return (inside);
}
