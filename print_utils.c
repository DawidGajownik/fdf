/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:08:53 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:54 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_last_line(unsigned char *pixel[4], int map_height[4],
		t_vars **vars, t_size s)
{
	int				mh[2];
	unsigned char	**p[2];

	p[0] = pixel[0];
	mh[0] = map_height[0];
	p[1] = pixel[1];
	mh[1] = map_height[1];
	if (pixel[0] && pixel[1]
		&& pixel_in_screen(pixel[0], &((*vars)->win_prop), &((*vars)->map_prop))
		&& pixel_in_screen(pixel[1], &((*vars)->win_prop), &((*vars)->map_prop))
		&& (*vars)->map_prop->width >= (*vars)->win_prop->cut_front
		&& (*vars)->map_prop->width <= s.width - (*vars)->win_prop->cut_back)
		draw_line(&((*vars)->map_prop), &((*vars)->win_prop), p, mh);
}

int	set_map_height(t_vars **vars, char **line)
{
	if ((*vars)->win_prop->z_down == 1)
		return (ft_atoi_hex(line[(*vars)->map_prop->width]));
	return (ft_atoi(line[(*vars)->map_prop->width]));
}

unsigned char	*set_point_data(int *map_height, t_vars **vars,
		char **line, t_size s)
{
	*map_height = set_map_height(vars, line);
	return (transformed_px(vars, s, *map_height));
}

unsigned char	*set_lower_point_data(int *map_height, t_vars **vars,
		char **line, t_size s)
{
	unsigned char	*pixel;

	(*vars)->map_prop->height++;
	pixel = set_point_data(map_height, vars, line, s);
	(*vars)->map_prop->height--;
	return (pixel);
}
