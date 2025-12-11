/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_quad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:07:33 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:07:33 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_poly(t_vec2 poly[4], t_vec2 p[5])
{
	poly[0] = p[1];
	poly[1] = p[2];
	poly[2] = p[4];
	poly[3] = p[3];
}

static void	set_first_min_max(t_vec2 *min, t_vec2 *max, t_vec2 p[5])
{
	min->x = p[1].x;
	max->x = p[1].x;
	min->y = p[1].y;
	max->y = p[1].y;
}

static void	set_min_max(t_vec2 *min, t_vec2 *max, t_vec2 p[5])
{
	if (p[2].x < min->x)
		min->x = p[2].x;
	if (p[3].x < min->x)
		min->x = p[3].x;
	if (p[4].x < min->x)
		min->x = p[4].x;
	if (p[2].x > max->x)
		max->x = p[2].x;
	if (p[3].x > max->x)
		max->x = p[3].x;
	if (p[4].x > max->x)
		max->x = p[4].x;
	if (p[2].y < min->y)
		min->y = p[2].y;
	if (p[3].y < min->y)
		min->y = p[3].y;
	if (p[4].y < min->y)
		min->y = p[4].y;
	if (p[2].y > max->y)
		max->y = p[2].y;
	if (p[3].y > max->y)
		max->y = p[3].y;
	if (p[4].y > max->y)
		max->y = p[4].y;
}

static void	paint_poly(t_win_prop **win_prop, int *map_height,
		t_vec2 p[5], int mh[4])
{
	if ((*win_prop)->z_down == 1)
		*map_height = weighted_color(p, mh);
	else
		*map_height = weighted_height(p, mh);
}

void	iterate_quad(t_map_prop **map_prop, t_win_prop **win_prop,
		unsigned char *px[4], int mh[4])
{
	t_vec2	min;
	t_vec2	max;
	int		map_height;
	t_vec2	p[5];
	t_vec2	poly[4];

	get_all_coords(px, map_prop, win_prop, p);
	set_poly(poly, p);
	set_first_min_max(&min, &max, p);
	set_min_max(&min, &max, p);
	p[0].y = min.y;
	while (p[0].y <= max.y)
	{
		p[0].x = min.x;
		while (p[0].x <= max.x)
		{
			if (point_in_poly(p[0].x, p[0].y, poly))
			{
				paint_poly(win_prop, &map_height, p, mh);
				paint_point(map_prop, win_prop, map_height, p[0]);
			}
			p[0].x++;
		}
		p[0].y++;
	}
}
