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

void	strings(t_vars **vars)
{
	if ((*vars)->win_prop->s_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 20, 0x00000000, "S - sphere view: OFF");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 20, 0x00FFFFFF, "S - sphere view: ON");
	}
	if ((*vars)->win_prop->s_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 20, 0x00000000, "S - sphere view: ON");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 20, 0x00FFFFFF, "S - sphere view: OFF");
	}
	if ((*vars)->win_prop->w_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 40, 0x00000000, "W - sphere: move");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 40, 0x00FFFFFF, "W - sphere: rotation");
	}
	if ((*vars)->win_prop->w_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 40, 0x00000000, "W - sphere: rotation");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 40, 0x00FFFFFF, "W - sphere: move");
	}
	if ((*vars)->win_prop->q_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 60, 0x00000000, "Q - rotate sphere: OFF");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 60, 0x00FFFFFF, "Q - rotate sphere: ON");
	}
	if ((*vars)->win_prop->q_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 60, 0x00000000, "Q - rotate sphere: ON");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 60, 0x00FFFFFF, "Q - rotate sphere: OFF");
	}
	if ((*vars)->win_prop->a_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 80, 0x00000000, "A - view: normal");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 80, 0x00FFFFFF, "A - view: side");
	}
	if ((*vars)->win_prop->a_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 80, 0x00000000, "A - view: side");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 80, 0x00FFFFFF, "A - view: normal");
	}
	mlx_string_put((*vars)->mlx, (*vars)->win, 20, 100, 0x00FFFFFF, "D & F - color correction");
	char *prev_color_scaler = ft_ftoa((*vars)->win_prop->prev_color_scaler, 2);
	char *color_scaler = ft_ftoa((*vars)->win_prop->color_scaler, 2);
	mlx_string_put((*vars)->mlx, (*vars)->win, 170, 100, 0x00000000, prev_color_scaler);
	mlx_string_put((*vars)->mlx, (*vars)->win, 170, 100, 0x00FFFFFF, color_scaler);
	(*vars)->win_prop->prev_color_scaler = (*vars)->win_prop->color_scaler;
	mlx_string_put((*vars)->mlx, (*vars)->win, 20, 120, 0x00FFFFFF, "E & R - topographic correction");
	char *prev_topo_scaler = ft_ftoa((*vars)->win_prop->prev_divider, 0);
	char *topo_scaler = ft_ftoa((*vars)->win_prop->divider, 0);
	mlx_string_put((*vars)->mlx, (*vars)->win, 210, 120, 0x00000000, prev_topo_scaler);
	mlx_string_put((*vars)->mlx, (*vars)->win, 210, 120, 0x00FFFFFF, topo_scaler);
	(*vars)->win_prop->prev_divider = (*vars)->win_prop->divider;
	if ((*vars)->win_prop->c_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 140, 0x00000000, "C - color scheme: earth");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 140, 0x00FFFFFF, "C - color scheme: moon");
	}
	if ((*vars)->win_prop->c_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 140, 0x00000000, "C - color scheme: moon");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 140, 0x00FFFFFF, "C - color scheme: earth");
	}
	if ((*vars)->win_prop->v_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 160, 0x00000000, "V - color fill: OFF");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 160, 0x00FFFFFF, "V - color fill: ON");
	}
	if ((*vars)->win_prop->v_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 160, 0x00000000, "V - color fill: ON");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 160, 0x00FFFFFF, "V - color fill: OFF");
	}
	if ((*vars)->win_prop->b_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 180, 0x00000000, "B - grid visible: OFF");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 180, 0x00FFFFFF, "B - grid visible: ON");
	}
	if ((*vars)->win_prop->b_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 180, 0x00000000, "B - grid visible: ON");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 180, 0x00FFFFFF, "B - grid visible: OFF");
	}
	mlx_string_put((*vars)->mlx, (*vars)->win, 20, 200, 0x00FFFFFF, "Mouse wheel - zoom:");
	char *prev_scale = ft_strjoin(ft_ftoa((*vars)->win_prop->prev_scale, 2), "x", 0);
	char *scale = ft_strjoin(ft_ftoa((*vars)->win_prop->scale, 2), "x", 0);
	mlx_string_put((*vars)->mlx, (*vars)->win, 190, 200, 0x00000000, prev_scale);
	mlx_string_put((*vars)->mlx, (*vars)->win, 190, 200, 0x00FFFFFF, scale);
	(*vars)->win_prop->prev_scale = (*vars)->win_prop->scale;
	mlx_string_put((*vars)->mlx, (*vars)->win, 20, 220, 0x00FFFFFF, "CTRL + mouse wheel - angle:");
	char *prev_angle = ft_strjoin(ft_ftoa((*vars)->map_prop->prev_grades*360/400, 0), "°", 1);
	char *angle = ft_strjoin(ft_ftoa((*vars)->map_prop->grades*360/400, 0), "°", 1);
	mlx_string_put((*vars)->mlx, (*vars)->win, 190, 220, 0x00000000, prev_angle);
	mlx_string_put((*vars)->mlx, (*vars)->win, 190, 220, 0x00FFFFFF, angle);
	(*vars)->map_prop->prev_grades = (*vars)->map_prop->grades;
	if ((*vars)->win_prop->x_down == 1)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 240, 0x00000000, "X - zooming object: OFF");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 240, 0x00FFFFFF, "X - zooming object: ON");
	}
	if ((*vars)->win_prop->x_down == 0)
	{
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 240, 0x00000000, "X - zooming object: ON");
		mlx_string_put((*vars)->mlx, (*vars)->win, 20, 240, 0x00FFFFFF, "X - zooming object: OFF");
	}
}

void	redraw(t_vars **vars)
{
	mlx_destroy_image((*vars)->mlx, (*vars)->img);
	(*vars)->img = mlx_new_image((*vars)->mlx,
			(*vars)->win_prop->width,
			(*vars)->win_prop->height);
	draw(vars, (*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img, 400, 0);
	strings(vars);
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
	mlx_key_hook((*vars)->win, key_hook, vars);
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
