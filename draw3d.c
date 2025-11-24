/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:17:36 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 16:17:38 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	pixel_in_screen(unsigned char *pixel,
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

static int	line_print(char **line,
	t_map_prop **map_prop, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int				width;
	int				map_height;

	width = (*map_prop)->width;
	(*map_prop)->width = 0;
	while (line[(*map_prop)->width])
	{
		map_height = ft_atoi(line[(*map_prop)->width]);
		pixel = transformed_px(map_prop, width, height, win_prop)
			+ offset_z(1000 / (*win_prop)->scale, map_height, map_prop);
		if (pixel && pixel_in_screen(pixel, win_prop, map_prop))
		{
			if ((*win_prop)->c_down == 1)
				set_moon_color(pixel, map_height);
			if ((*win_prop)->c_down == 0)
				set_hipsometric_color(pixel, map_height, map_prop, win_prop);
		}
		(*map_prop)->width++;
	}
	return (0);
}

static void	set_scale(t_win_prop **win_prop, t_map_prop **map_prop)
{
	if ((*win_prop)->scale == 0)
	{
		if ((*win_prop)->width / (*map_prop)->width
			< (*win_prop)->height / (*map_prop)->height)
			(*win_prop)->scale = (*win_prop)->width / ((*map_prop)->width);
		else
			(*win_prop)->scale = (*win_prop)->height / ((*map_prop)->height);
	}
	if ((*win_prop)->scale == 0)
		(*win_prop)->scale = 1;
}

int	draw(char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;
	int		height;

	set_scale(win_prop, map_prop);
	height = (*map_prop)->height;
	(*map_prop)->height = 0;
	while (file_split[(*map_prop)->height] != NULL)
	{
		line = ft_split(file_split[(*map_prop)->height], ' ');
		if (!line)
			return (-1);
		line_print(line, map_prop, win_prop, height);
		free_mlx(line, NULL, NULL);
		(*map_prop)->height++;
	}
	return (0);
}
