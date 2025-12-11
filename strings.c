/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:07:43 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/10 14:07:44 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	strings_five(t_vars **vars, void *mlx, void *win, int c[2])
{
	if ((*vars)->win_prop->c_down == 0)
	{
		mlx_string_put(mlx, win, 20, 140, c[0], "C - color scheme: moon");
		mlx_string_put(mlx, win, 20, 140, c[1], "C - color scheme: blue");
	}
	if ((*vars)->win_prop->v_down == 1)
	{
		mlx_string_put(mlx, win, 20, 160, c[0], "V - color fill: OFF");
		mlx_string_put(mlx, win, 20, 160, c[1], "V - color fill: ON");
	}
	if ((*vars)->win_prop->v_down == 0)
	{
		mlx_string_put(mlx, win, 20, 160, c[0], "V - color fill: ON");
		mlx_string_put(mlx, win, 20, 160, c[1], "V - color fill: OFF");
	}
	if ((*vars)->win_prop->b_down == 1)
	{
		mlx_string_put(mlx, win, 20, 180, c[0], "B - grid visible: OFF");
		mlx_string_put(mlx, win, 20, 180, c[1], "B - grid visible: ON");
	}
	if ((*vars)->win_prop->b_down == 0)
	{
		mlx_string_put(mlx, win, 20, 180, c[0], "B - grid visible: ON");
		mlx_string_put(mlx, win, 20, 180, c[1], "B - grid visible: OFF");
	}
}

void	strings_four(t_vars **vars, void *mlx, void *win, int c[2])
{
	(*vars)->win_prop->prev_divider = (*vars)->win_prop->divider;
	if ((*vars)->win_prop->c_down == 4)
		mlx_string_put(mlx, win, 20, 140, c[0], "C - color scheme: earth");
	if ((*vars)->win_prop->c_down == 4)
		mlx_string_put(mlx, win, 20, 140, c[1], "C - color scheme: moon");
	if ((*vars)->win_prop->c_down == 3)
		mlx_string_put(mlx, win, 20, 140, c[0], "C - color scheme: red");
	if ((*vars)->win_prop->c_down == 3)
		mlx_string_put(mlx, win, 20, 140, c[1], "C - color scheme: earth");
	if ((*vars)->win_prop->c_down == 2)
		mlx_string_put(mlx, win, 20, 140, c[0], "C - color scheme: green");
	if ((*vars)->win_prop->c_down == 2)
		mlx_string_put(mlx, win, 20, 140, c[1], "C - color scheme: red");
	if ((*vars)->win_prop->c_down == 1)
		mlx_string_put(mlx, win, 20, 140, c[0], "C - color scheme: blue");
	if ((*vars)->win_prop->c_down == 1)
		mlx_string_put(mlx, win, 20, 140, c[1], "C - color scheme: green");
}

void	strings_three(t_vars **vars, void *mlx, void *win, int c[2])
{
	char	*prev_color_scaler;
	char	*color_scaler;
	char	*prev_topo_scaler;
	char	*topo_scaler;

	if ((*vars)->win_prop->a_down == 1)
		mlx_string_put(mlx, win, 20, 80, c[0], "A - view: normal");
	if ((*vars)->win_prop->a_down == 1)
		mlx_string_put(mlx, win, 20, 80, c[1], "A - view: side");
	if ((*vars)->win_prop->a_down == 0)
		mlx_string_put(mlx, win, 20, 80, c[0], "A - view: side");
	if ((*vars)->win_prop->a_down == 0)
		mlx_string_put(mlx, win, 20, 80, c[1], "A - view: normal");
	mlx_string_put(mlx, win, 20, 100, c[1], "D & F - color correction");
	prev_color_scaler = ft_ftoa((*vars)->win_prop->prev_color_scaler, 2);
	color_scaler = ft_ftoa((*vars)->win_prop->color_scaler, 2);
	mlx_string_put(mlx, win, 170, 100, c[0], prev_color_scaler);
	mlx_string_put(mlx, win, 170, 100, c[1], color_scaler);
	(*vars)->win_prop->prev_color_scaler = (*vars)->win_prop->color_scaler;
	mlx_string_put(mlx, win, 20, 120, c[1], "E & R - topographic correction");
	prev_topo_scaler = ft_ftoa((*vars)->win_prop->prev_divider, 0);
	topo_scaler = ft_ftoa((*vars)->win_prop->divider, 0);
	mlx_string_put(mlx, win, 210, 120, c[0], prev_topo_scaler);
	mlx_string_put(mlx, win, 210, 120, c[1], topo_scaler);
	free_ftoa(prev_color_scaler, color_scaler, prev_topo_scaler, topo_scaler);
}

void	strings_two(t_vars **vars, void *mlx, void *win, int c[2])
{
	if ((*vars)->win_prop->s_down == 1)
		mlx_string_put(mlx, win, 20, 20, c[0], "S - sphere view: OFF");
	if ((*vars)->win_prop->s_down == 1)
		mlx_string_put(mlx, win, 20, 20, c[1], "S - sphere view: ON");
	if ((*vars)->win_prop->s_down == 0)
		mlx_string_put(mlx, win, 20, 20, c[0], "S - sphere view: ON");
	if ((*vars)->win_prop->s_down == 0)
		mlx_string_put(mlx, win, 20, 20, c[1], "S - sphere view: OFF");
	if ((*vars)->win_prop->w_down == 1)
		mlx_string_put(mlx, win, 20, 40, c[0], "W - sphere: move");
	if ((*vars)->win_prop->w_down == 1)
		mlx_string_put(mlx, win, 20, 40, c[1], "W - sphere: rotation");
	if ((*vars)->win_prop->w_down == 0)
		mlx_string_put(mlx, win, 20, 40, c[0], "W - sphere: rotation");
	if ((*vars)->win_prop->w_down == 0)
		mlx_string_put(mlx, win, 20, 40, c[1], "W - sphere: move");
	if ((*vars)->win_prop->q_down == 1)
		mlx_string_put(mlx, win, 20, 60, c[0], "Q - rotate sphere: OFF");
	if ((*vars)->win_prop->q_down == 1)
		mlx_string_put(mlx, win, 20, 60, c[1], "Q - rotate sphere: ON");
	if ((*vars)->win_prop->q_down == 0)
		mlx_string_put(mlx, win, 20, 60, c[0], "Q - rotate sphere: ON");
	if ((*vars)->win_prop->q_down == 0)
		mlx_string_put(mlx, win, 20, 60, c[1], "Q - rotate sphere: OFF");
}

void	strings_one(t_vars **vars, void *mlx, void *win, int c[2])
{
	char	*ftoa[4];
	char	*string[4];

	mlx_string_put(mlx, win, 20, 200, c[1], "Mouse wheel - zoom:");
	ftoa[0] = ft_ftoa((*vars)->win_prop->prev_scale, 2);
	string[0] = ft_strjoin(ftoa[0], "x", 0);
	ftoa[1] = ft_ftoa((*vars)->win_prop->scale, 2);
	string[1] = ft_strjoin(ftoa[1], "x", 0);
	mlx_string_put(mlx, win, 190, 200, c[0], string[0]);
	mlx_string_put(mlx, win, 190, 200, c[1], string[1]);
	(*vars)->win_prop->prev_scale = (*vars)->win_prop->scale;
	mlx_string_put(mlx, win, 20, 220, c[1], "CTRL + mouse wheel - angle:");
	ftoa[2] = ft_ftoa((*vars)->map_prop->prev_grades * 360 / 400, 0);
	string[2] = ft_strjoin(ftoa[2], "°", 1);
	ftoa[3] = ft_ftoa((*vars)->map_prop->grades * 360 / 400, 0);
	string[3] = ft_strjoin(ftoa[3], "°", 1);
	mlx_string_put(mlx, win, 190, 220, c[0], string[2]);
	mlx_string_put(mlx, win, 190, 220, c[1], string[3]);
	(*vars)->map_prop->prev_grades = (*vars)->map_prop->grades;
	if ((*vars)->win_prop->x_down == 1)
		mlx_string_put(mlx, win, 20, 240, c[0], "X - zooming object: OFF");
	if ((*vars)->win_prop->x_down == 1)
		mlx_string_put(mlx, win, 20, 240, c[1], "X - zooming object: ON");
	free_ftoa(ftoa[0], ftoa[1], ftoa[2], ftoa[3]);
	free_ftoa(string[0], string[1], string[2], string[3]);
}
