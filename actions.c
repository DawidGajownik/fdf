/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:12:02 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:07 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_vars **vars)
{
	mlx_destroy_image((*vars)->mlx, (*vars)->img);
	(*vars)->img = mlx_new_image((*vars)->mlx,
			(*vars)->win_prop->width,
			(*vars)->win_prop->height);
	draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img, 400, 0);
}

void	redraw_object(t_vars **vars)
{
	if ((*vars)->object)
	{
		mlx_destroy_image((*vars)->mlx, (*vars)->object->img);
		(*vars)->object->img = mlx_new_image((*vars)->mlx,
				(*vars)->win_prop->width / 4, (*vars)->win_prop->height / 4);
		draw_object((*vars)->object, &(*vars)->win_prop);
		mlx_put_image_to_window((*vars)->mlx, (*vars)->win,
			(*vars)->object->img, 0, 0);
	}
}

int	actions(t_vars **vars)
{
	mlx_hook((*vars)->win, 4, 1L << 2, mouse_press, vars);
	mlx_hook((*vars)->win, 5, 1L << 3, mouse_release, vars);
	mlx_hook((*vars)->win, 6, 1L << 6, mouse_move, vars);
	mlx_hook((*vars)->win, 2, 1L << 0, key_press, vars);
	mlx_hook((*vars)->win, 3, 1L << 1, key_release, vars);
	return (0);
}

int	globe_move(void *param)
{
	t_vars	**vars;

	vars = (t_vars **)param;
	if ((*vars)->win_prop->q_down)
	{
		usleep(50000);
		(*vars)->win_prop->sphere_correction_x += 1;
		redraw(vars);
		if ((*vars)->object)
		{
			(*vars)->object->offset_x += 1;
			redraw_object(vars);
		}
	}
}
