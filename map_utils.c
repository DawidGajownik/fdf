/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:00:24 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 16:00:25 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	set_width(char **line, t_map_prop **map_prop)
{
	int		rows;

	rows = 0;
	while (line[rows] != NULL)
	{
		if ((*map_prop)->height_offset > ft_atoi(line[rows]))
			(*map_prop)->height_offset = ft_atoi(line[rows]);
		if ((*map_prop)->low_high_diff < ft_atoi(line[rows])
			- (*map_prop)->height_offset)
			(*map_prop)->low_high_diff = ft_atoi(line[rows])
				- (*map_prop)->height_offset;
		rows++;
		if ((*map_prop)->width == 0 || (*map_prop)->width < rows)
			(*map_prop)->width = rows;
		if ((*map_prop)->width != rows)
			return (-1);
	}
	return (0);
}

int	set_res(char **file_split, t_map_prop **map_prop)
{
	char	**line;

	while (file_split[(*map_prop)->height] != NULL)
	{
		line = ft_split(file_split[(*map_prop)->height], ' ');
		if (!line)
			return (-1);
		(*map_prop)->width = 0;
		if (set_width(line, map_prop) < 0)
			return (-1);
		free_mlx(line, NULL, NULL);
		(*map_prop)->height++;
	}
	if ((*map_prop)->low_high_diff > 256)
		(*map_prop)->low_high_diff = 256;
	return (0);
}

static int	set_width_this(char **line, t_object *object)
{
	int		rows;

	rows = 0;
	while (line[rows] != NULL)
	{
		// if (object->height_offset > ft_atoi(line[rows]))
		// 	object->height_offset = ft_atoi(line[rows]);
		// if (object->low_high_diff < ft_atoi(line[rows])
		// 	- object->height_offset)
		// 	object->low_high_diff = ft_atoi(line[rows])
		// 		- object->height_offset;
		rows++;
		if (object->width == 0 || object->width < rows)
			object->width = rows;
		if (object->width != rows)
			return (-1);
	}
	return (0);
}

int	set_res_object(t_object *object)
{
	char	**line;
	while (object->file_split[object->height] != NULL)
	{
		line = ft_split(object->file_split[object->height], ' ');
		if (!line)
			return (-1);
		object->width = 0;
		if (set_width_this(line, object) < 0)
			return (-1);
		free_mlx(line, NULL, NULL);
		object->height++;
	}
	//if (object->low_high_diff > 256)
	//	object->low_high_diff = 256;
	return (0);
}

void	set_padding(t_win_prop **win_prop, t_map_prop **map_prop)
{
	if ((*win_prop)->height / (*map_prop)->height
		< (*win_prop)->width / (*map_prop)->width)
		(*win_prop)->scale = (*win_prop)->height / (*map_prop)->height;
	else
		(*win_prop)->scale = (*win_prop)->width / (*map_prop)->width;
	if ((*win_prop)->scale > 5)
		(*win_prop)->padding = 1;
}
