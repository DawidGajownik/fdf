/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:14:42 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:14:43 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	pixel_in_screen_object(unsigned char *pixel,
	t_win_prop **win_prop, t_object **object)
{
	unsigned char	*start;
	unsigned char	*end;

	start = (*object)->img_data;
	end = start + (*win_prop)->height * (*win_prop)->height / 2;
	if (pixel < start || pixel >= end)
		return (NULL);
	return ('t');
}

int	centering_offset_y_object(t_object *object, int height)
{
	int	offset_y;

	offset_y = (object->height - height * object->scale);
	return (offset_y / 2);
}

int	centering_offset_x_object(t_object *object, int width)
{
	int	offset_x;

	offset_x = (object->width - width * object->scale);
	return (offset_x / 2);
}

int	line_print_object(char **line, t_object *object,
	t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int				width;
	int				map_height;

	map_height = 0;
	width = object->width;
	object->width = 0;
	while (line[object->width])
	{
		map_height = ft_atoi(line[object->width]);
		pixel = transformed_px_object(object, width, height, win_prop);
		if (pixel && pixel_in_screen_object(pixel, win_prop, &object))
			set_moon_color(pixel, map_height);
		object->width++;
	}
	return (0);
}

int	draw_object(t_object *object, t_win_prop **win_prop)
{
	char	**line;
	int		height;

	if (object->scale == 0)
	{
		if ((*win_prop)->width / object->width
			< (*win_prop)->height / object->height)
			object->scale = (*win_prop)->width / (object->width);
		else
			object->scale = (*win_prop)->height / (object->height);
	}
	if (object->scale == 0)
		object->scale = 1;
	height = object->height;
	object->height = 0;
	while (object->file_split[object->height] != NULL)
	{
		line = ft_split(object->file_split[object->height], ' ');
		if (!line)
			return (-1);
		line_print_object(line, object, win_prop, height);
		free_mlx(line, NULL, NULL);
		object->height++;
	}
	return (0);
}
