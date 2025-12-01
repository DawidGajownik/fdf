/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:00:34 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 16:00:35 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static void	set_color(t_map_prop **map_prop,
t_win_prop **win_prop, int i, char **line)
{
	int				j;
	int				map_height;
	unsigned char	*pixel;

	j = 0;
	while (j < (*win_prop)->scale - (*win_prop)->padding)
	{
		pixel = (*map_prop)->img_data + (*map_prop)->width
			* (*map_prop)->bytes_pp * (*win_prop)->scale + i
			* (*map_prop)->bytes_pp + (*map_prop)->height
			* (*map_prop)->line_size * (*win_prop)->scale
			+ (*map_prop)->line_size * j;
		map_height = ft_atoi(line[(*map_prop)->width]);
		*(unsigned int *)pixel = 0x00FFFFFF - 256 * 256
			* (map_height - (*map_prop)->height_offset)
			* (256 / (*map_prop)->low_high_diff) - 256
			* (map_height - (*map_prop)->height_offset)
			* (256 / (*map_prop)->low_high_diff);
		j++;
	}
}*/

/*static int	point_gen(char **line, t_map_prop **map_prop, t_win_prop **win_prop)
{
	int				i;

	(*map_prop)->width = 0;
	while (line[(*map_prop)->width])
	{
		i = 0;
		while (i < (*win_prop)->scale - (*win_prop)->padding)
		{
			set_color(map_prop, win_prop, i, line);
			i++;
		}
		(*map_prop)->width++;
	}
	return (0);
}*/

/*int	img_gen(char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;

	(*map_prop)->height = 0;
	while (file_split[(*map_prop)->height] != NULL)
	{
		line = ft_split(file_split[(*map_prop)->height], ' ');
		if (!line || point_gen(line, map_prop, win_prop) < 0)
			return (-1);
		free_mlx(line, NULL, NULL);
		(*map_prop)->height++;
	}
	return (0);
}*/
