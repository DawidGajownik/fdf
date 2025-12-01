/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:03:18 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 17:03:19 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_hook(int keycode, void *param)
{
	t_vars	**vars;

	ft_printf("%d\n", keycode);
	vars = (t_vars **)param;
	if (keycode == 105)
    {
		ft_printf("x = %d\ny = %d\ncf = %d, cb = %d", (*vars)->win_prop->sphere_correction_x, (*vars)->win_prop->sphere_correction_y, (*vars)->win_prop->cut_front, (*vars)->win_prop->cut_back);
    }
	if (keycode == 107)
    {
        (*vars)->win_prop->cut_front -= 1;
    }
	if (keycode == 108)
    {
        (*vars)->win_prop->cut_back -= 1;
    }
	if (keycode == 111)
    {
        (*vars)->win_prop->cut_front += 1;
    }
	if (keycode == 112)
    {
        (*vars)->win_prop->cut_back += 1;
    }
    if (keycode == 101)
    {
        (*vars)->win_prop->divider += 50;
		redraw(vars);
    }
    if (keycode == 114 && (*vars)->win_prop->divider > 50)
    {
		(*vars)->win_prop->divider -= 50;
		redraw(vars);
    }
	if (keycode == 102)
    {
        (*vars)->win_prop->color_scaler += 0.05;
		redraw(vars);
    }
	if (keycode == 100)
    {
        (*vars)->win_prop->color_scaler -= 0.05;
		redraw(vars);
    }
}

void	keys_map_rest(int keycode, t_vars **vars)
{
	if (keycode == 119 && !(*vars)->win_prop->w_down)
		(*vars)->win_prop->w_down = 1;
	else if (keycode == 119 && (*vars)->win_prop->w_down)
		(*vars)->win_prop->w_down = 0;
	if (keycode == 115 && !(*vars)->win_prop->s_down)
		(*vars)->win_prop->s_down = 1;
	else if (keycode == 115 && (*vars)->win_prop->s_down)
		(*vars)->win_prop->s_down = 0;
	if (keycode == 120 && !(*vars)->win_prop->x_down)
		(*vars)->win_prop->x_down = 1;
	else if (keycode == 120 && (*vars)->win_prop->x_down)
		(*vars)->win_prop->x_down = 0;
	if (keycode == 118 && !(*vars)->win_prop->v_down)
		(*vars)->win_prop->v_down = 1;
	else if (keycode == 118 && (*vars)->win_prop->v_down)
		(*vars)->win_prop->v_down = 0;
	if (keycode == 98 && !(*vars)->win_prop->b_down)
		(*vars)->win_prop->b_down = 1;
	else if (keycode == 98 && (*vars)->win_prop->b_down)
		(*vars)->win_prop->b_down = 0;
	if (keycode == 65507)
		(*vars)->win_prop->ctrl_down = 1;
}

void	keys_map(int keycode, t_vars **vars)
{
	if (keycode == 113 && !(*vars)->win_prop->q_down)
		(*vars)->win_prop->q_down = 1;
	else if (keycode == 113 && (*vars)->win_prop->q_down)
		(*vars)->win_prop->q_down = 0;
	if (keycode == 99 && !(*vars)->win_prop->c_down)
		(*vars)->win_prop->c_down = 1;
	else if (keycode == 99 && (*vars)->win_prop->c_down)
		(*vars)->win_prop->c_down = 0;
	if (keycode == 97 && !(*vars)->win_prop->a_down)
		(*vars)->win_prop->a_down = 1;
	else if (keycode == 97 && (*vars)->win_prop->a_down)
		(*vars)->win_prop->a_down = 0;
	keys_map_rest(keycode, vars);
	key_hook(keycode, vars);
}

int	key_press(int keycode, void *param)
{
	t_vars	**vars;

	vars = (t_vars **)param;
	keys_map(keycode, vars);
	redraw(vars);
	redraw_object(vars);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_vars	**vars;

	vars = (t_vars **)param;
	if (keycode == 65507)
		(*vars)->win_prop->ctrl_down = 0;
	return (0);
}
