/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:08:20 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:21 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_all_coords(unsigned char *px[4], t_map_prop **map_prop,
		t_win_prop **win_prop, t_vec2 p[5])
{
	get_coords_from_addr(px[0], map_prop, win_prop, &p[1]);
	get_coords_from_addr(px[1], map_prop, win_prop, &p[2]);
	get_coords_from_addr(px[2], map_prop, win_prop, &p[3]);
	get_coords_from_addr(px[3], map_prop, win_prop, &p[4]);
}

int	draw_line(t_map_prop **map_prop, t_win_prop **win_prop,
		char *pixel[2], int map_height[2])
{
	t_vec2	p[2];

	get_coords_from_addr(pixel[0], map_prop, win_prop, &p[0]);
	get_coords_from_addr(pixel[1], map_prop, win_prop, &p[1]);
	bresenham(p, map_prop, win_prop, map_height);
}

char	pixel_in_screen(unsigned char *pixel,
	t_win_prop **win_prop, t_map_prop **map_prop)
{
	unsigned char	*start;
	unsigned char	*end;

	start = (*map_prop)->img_data;
	end = start + (*win_prop)->height * (*win_prop)->height * 8;
	if (pixel < start || pixel >= end)
		return (NULL);
	return ('t');
}

static void	print_all(unsigned char **pixel[4], t_vars **vars,
		t_size s, int map_height[4])
{
	int				mh[2];
	unsigned char	**p[2];

	p[0] = pixel[0];
	mh[0] = map_height[0];
	p[1] = pixel[2];
	mh[1] = map_height[2];
	if (pixel[0] && pixel[1] && pixel[2] && pixel[3]
		&& pixel_in_screen(pixel[0], &((*vars)->win_prop), &((*vars)->map_prop))
		&& pixel_in_screen(pixel[1], &((*vars)->win_prop), &((*vars)->map_prop))
		&& pixel_in_screen(pixel[2], &((*vars)->win_prop), &((*vars)->map_prop))
		&& pixel_in_screen(pixel[3], &((*vars)->win_prop), &((*vars)->map_prop))
		&& (*vars)->map_prop->width >= (*vars)->win_prop->cut_front
		&& (*vars)->map_prop->width <= s.width - (*vars)->win_prop->cut_back)
	{
		if ((*vars)->map_prop->height < s.height - 1
			&& (*vars)->win_prop->v_down == 1)
			iterate_quad(&((*vars)->map_prop), &((*vars)->win_prop), pixel,
				map_height);
		if ((*vars)->map_prop->height < s.height - 1)
			draw_line(&((*vars)->map_prop), &((*vars)->win_prop), p, mh);
	}
	print_last_line(pixel, map_height, vars, s);
}

int	line_print(char **line[2], t_vars **vars, t_size s)
{
	unsigned char	*pixel[4];
	int				map_height[4];

	pixel[0] = NULL;
	pixel[1] = NULL;
	pixel[2] = NULL;
	pixel[3] = NULL;
	s.width = (*vars)->map_prop->width;
	(*vars)->map_prop->width = 0;
	while (line[0][((*vars)->map_prop)->width])
	{
		pixel[0] = set_point_data(&map_height[0], vars, line[0], s);
		if (line[1] && line[1][(*vars)->map_prop->width])
			pixel[2] = set_lower_point_data(&map_height[2], vars, line[1], s);
		(*vars)->map_prop->width++;
		if (line[0][(*vars)->map_prop->width])
			pixel[1] = set_point_data(&map_height[1], vars, line[0], s);
		if (line[1] && line[1][(*vars)->map_prop->width]
			&& (*vars)->map_prop->width < s.width)
			pixel[3] = set_lower_point_data(&map_height[3], vars, line[1], s);
		print_all(pixel, vars, s, map_height);
	}
	return (0);
}
