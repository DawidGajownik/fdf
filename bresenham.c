/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:05:49 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:05:51 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	pixel_in_bounds(t_vec2 p, t_win_prop **w)
{
	int	hx;
	int	hy;

	hx = (*w)->width / 2;
	hy = (*w)->height / 2;
	return (!(p.x <= -hx + 1 || p.x >= hx - 10
			|| p.y <= -hy || p.y >= hy));
}

unsigned char	*get_pixel_addr(t_vec2 p, t_map_prop **mp, t_win_prop **w)
{
	return ((*mp)->img_data
		+ (((*w)->height / 2 - p.y) * (*mp)->line_size)
		+ ((p.x + (*w)->width / 2) * (*mp)->bytes_pp));
}

void	bresenham(t_vec2 p[2],
		t_map_prop **mp, t_win_prop **win,
		int h[2])
{
	t_bres			b;
	unsigned char	*px;

	b = bres_setup(p[0], p[1]);
	b.p0 = p[0];
	b.full = distance(p[0], p[1]);
	while (1)
	{
		if (!pixel_in_bounds(b.p, win))
			return ;
		px = get_pixel_addr(b.p, mp, win);
		bres_pixel(px, bres_height(&b, win, h[0], h[1]), mp, win);
		if (b.p.x == p[1].x && b.p.y == p[1].y)
			break ;
		bres_step(&b);
	}
}
