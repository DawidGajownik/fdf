/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_quad_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:07:48 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:07:49 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	dist(t_vec2 a, t_vec2 b)
{
	float	dx;
	float	dy;

	dx = (float)a.x - (float)b.x;
	dy = (float)a.y - (float)b.y;
	return (sqrtf(dx * dx + dy * dy));
}

static void	set_dist(float d[4], t_vec2 p[5])
{
	d[0] = dist(p[0], p[1]);
	d[1] = dist(p[0], p[2]);
	d[2] = dist(p[0], p[3]);
	d[3] = dist(p[0], p[4]);
}

static void	set_colors(t_color col, int c[4], float w[4], int sum)
{
	col.r[1] = (c[0] >> 16) & 0xFF;
	col.g[1] = (c[0] >> 8) & 0xFF;
	col.b[1] = c[0] & 0xFF;
	col.r[2] = (c[1] >> 16) & 0xFF;
	col.g[2] = (c[1] >> 8) & 0xFF;
	col.b[2] = c[1] & 0xFF;
	col.r[3] = (c[2] >> 16) & 0xFF;
	col.g[3] = (c[2] >> 8) & 0xFF;
	col.b[3] = c[2] & 0xFF;
	col.r[4] = (c[3] >> 16) & 0xFF;
	col.g[4] = (c[3] >> 8) & 0xFF;
	col.b[4] = c[3] & 0xFF;
	col.r[0] = (int)((w[0] * col.r[1] + w[1] * col.r[2] + w[2]
				* col.r[3] + w[3] * col.r[4]) / sum);
	col.g[0] = (int)((w[0] * col.g[1] + w[1] * col.g[2] + w[2]
				* col.g[3] + w[3] * col.g[4]) / sum);
	col.b[0] = (int)((w[0] * col.b[1] + w[1] * col.b[2] + w[2]
				* col.b[3] + w[3] * col.b[4]) / sum);
}

int	weighted_color(t_vec2 p[5], int c[4])
{
	float	d[4];
	float	w[4];
	float	sum;
	t_color	col;

	set_dist(d, p);
	if (d[0] == 0)
		return (c[0]);
	if (d[1] == 0)
		return (c[1]);
	if (d[2] == 0)
		return (c[2]);
	if (d[3] == 0)
		return (c[3]);
	w[0] = 1.0f / d[0];
	w[1] = 1.0f / d[1];
	w[2] = 1.0f / d[2];
	w[3] = 1.0f / d[3];
	sum = w[1] + w[2] + w[3] + w[0];
	set_colors(col, c, w, sum);
	return ((col.r[0] << 16) | (col.g[0] << 8) | col.b[0]);
}

int	weighted_height(t_vec2 p[5], int mh[4])
{
	float	d[4];
	float	w[4];
	float	sum;
	int		result;

	set_dist(d, p);
	if (d[0] == 0)
		return (mh[0]);
	if (d[1] == 0)
		return (mh[1]);
	if (d[2] == 0)
		return (mh[2]);
	if (d[3] == 0)
		return (mh[3]);
	w[0] = 1.0f / d[0];
	w[1] = 1.0f / d[1];
	w[2] = 1.0f / d[2];
	w[3] = 1.0f / d[3];
	sum = w[0] + w[1] + w[2] + w[3];
	result = ((int)((w[0] * mh[0] + w[1] * mh[1]
					+ w[2] * mh[2] + w[3] * mh[3]) / sum));
	return (result);
}
