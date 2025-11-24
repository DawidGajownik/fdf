/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:06:11 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 17:06:12 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_roll(int button, t_vars **vars)
{
	if ((button == 4 || button == 5)
		&& !(*vars)->win_prop->ctrl_down)
	{
		if (button == 4)
		{
			if ((*vars)->object && (*vars)->win_prop->x_down == 1)
				(*vars)->object->scale++;
			else
				(*vars)->win_prop->scale++;
		}
		else
		{
			if ((*vars)->object && (*vars)->win_prop->x_down == 1
				&& (*vars)->object->scale > 1)
				(*vars)->object->scale--;
			else if ((*vars)->win_prop->x_down == 0
				&& (*vars)->win_prop->scale > 1)
				(*vars)->win_prop->scale--;
		}
	}
	redraw(vars);
	redraw_object(vars);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_vars	**vars;
	int		delta_angle;

	vars = (t_vars **)param;
	if (button == 1)
	{
		(*vars)->win_prop->mouse_down = 1;
		(*vars)->win_prop->last_x = x;
		(*vars)->win_prop->last_y = y;
	}
	if ((*vars)->win_prop->ctrl_down && (button == 4 || button == 5))
	{
		if (button == 4)
			delta_angle = 5;
		else
			delta_angle = -5;
		(*vars)->map_prop->grades
			= ((*vars)->map_prop->grades + delta_angle + 400) % 400;
		redraw(vars);
		redraw_object(vars);
		return (0);
	}
	mouse_roll(button, vars);
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_vars	**vars;

	vars = (t_vars **)param;
	if (button == 1)
		(*vars)->win_prop->mouse_down = 0;
	return (0);
}

void	move_correction(t_vars **vars, int dx, int dy)
{
	if ((*vars)->win_prop->w_down && (*vars)->win_prop->s_down == 1)
	{
		(*vars)->win_prop->sphere_correction_x += dx;
		(*vars)->win_prop->sphere_correction_y += dy;
	}
	else
	{
		(*vars)->win_prop->offset_x += dx;
		(*vars)->win_prop->offset_y += dy;
	}
}

int	mouse_move(int x, int y, void *param)
{
	t_vars	**vars;
	int		dx;
	int		dy;

	vars = (t_vars **)param;
	dx = x - (*vars)->win_prop->last_x;
	dy = y - (*vars)->win_prop->last_y;
	if ((*vars)->win_prop->mouse_down
		&& (dx > 25 || dy > 25 || dx < -25 || dy < -25))
	{
		move_correction(vars, dx, dy);
		(*vars)->win_prop->last_x = x;
		(*vars)->win_prop->last_y = y;
		redraw(vars);
		if ((*vars)->object && (*vars)->object->img)
		{
			(*vars)->object->offset_x += dx;
			(*vars)->object->offset_y += dy;
			(*vars)->object->last_x = x;
			(*vars)->object->last_y = y;
			redraw_object(vars);
		}
	}
	return (0);
}
