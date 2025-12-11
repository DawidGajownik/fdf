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

static int	set_scale(t_win_prop **win_prop, t_map_prop **map_prop)
{
	if ((*map_prop)->width == 0)
		return (-1);
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
	return (0);
}

static void	free_lines(char	**line[2], t_vars **vars, char **file_split)
{
	free_mlx(line[0], NULL, NULL);
	if (line[1] && file_split[(*vars)->map_prop->height + 1] != NULL)
		free_mlx(line[1], NULL, NULL);
	if (line[1])
		line[1] = NULL;
}

int	draw(t_vars **vars, char **file_split,
	t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line[2];
	t_size	s;

	line[1] = NULL;
	if (set_scale(win_prop, map_prop) < 0)
		return (-1);
	s.height = (*map_prop)->height;
	(*map_prop)->height = 0;
	while (file_split[(*map_prop)->height] != NULL)
	{
		line[0] = ft_split(file_split[(*map_prop)->height], ' ');
		if (file_split[(*vars)->map_prop->height + 1] != NULL)
		{
			line[1] = ft_split(file_split[(*map_prop)->height + 1], ' ');
			if (!line[1])
				return (-1);
		}
		if (!line[0])
			return (-1);
		line_print(line, vars, s);
		free_lines(line, vars, file_split);
		(*map_prop)->height++;
	}
	strings(vars);
	return (0);
}
