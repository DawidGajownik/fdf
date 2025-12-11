/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bresenham.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:07:17 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:07:18 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bres	bres_setup(t_vec2 p, t_vec2 n)
{
	t_bres	b;

	b.p = p;
	b.n = n;
	b.dx = abs(n.x - p.x);
	b.sx = (p.x < n.x);
	if (!b.sx)
		b.sx = -1;
	b.dy = -abs(n.y - p.y);
	b.sy = (p.y < n.y);
	if (!b.sy)
		b.sy = -1;
	b.err = b.dx + b.dy;
	return (b);
}

int	bres_height(t_bres *b, t_win_prop **win, int h1, int h2)
{
	float	dist;
	float	t;

	dist = distance(b->p0, b->p);
	if (b->full == 0)
		t = 0;
	else
		t = dist / b->full;
	if ((*win)->z_down)
		return (lerp_color(h1, h2, t));
	return ((int)((1.0f - t) * h1 + t * h2));
}

void	bres_pixel(unsigned char *px, int mh,
		t_map_prop **mp, t_win_prop **win)
{
	if ((*win)->z_down)
	{
		*(unsigned int *)px = mh;
		return ;
	}
	if ((*win)->c_down == 0)
		set_color_blue(px, mh, win, 0);
	else if ((*win)->c_down == 1)
		set_color_green(px, mh, win, 0);
	else if ((*win)->c_down == 2)
		set_color_red(px, mh, win, 0);
	else if ((*win)->c_down == 4)
		set_moon_color(px, mh, win, 0);
	else if ((*win)->c_down == 3)
		set_hipsometric_color(px, mh, mp, win);
}

void	bres_step(t_bres *b)
{
	b->e2 = 2 * b->err;
	if (b->e2 >= b->dy)
	{
		b->err += b->dy;
		b->p.x += b->sx;
	}
	if (b->e2 <= b->dx)
	{
		b->err += b->dx;
		b->p.y += b->sy;
	}
}
