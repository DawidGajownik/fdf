/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:36:41 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:36:43 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned char	*transformed_px_object(t_object *object,
	int width, int height, t_win_prop **win_prop)
{
	int		half_x;
	int		half_y;
	t_vec2	w_h;
	t_vec2	p;

	object->grades = 0;
	half_x = (*win_prop)->width / 2;
	half_y = (*win_prop)->height / 2;
	p.x = (object->width * object->scale / 4 - (*win_prop)->width / 2);
	p.y = -(object->height * object->scale / 4 - (*win_prop)->height / 2);
	p.x = (int)round(p.x * cos(object->grades * M_PI / 200.0)
			- p.y * sin(object->grades * M_PI / 200.0)) + object->offset_x;
	p.y = (int)round(p.x * sin(object->grades * M_PI / 200.0)
			+ p.y * cos(object->grades * M_PI / 200.0));
	w_h.x = width * 1 / 4;
	w_h.y = height * 1 / 4;
	p = map_to_sphere(p, w_h, height / 2 * object->scale
			/ 4, height / 2 * 1 / 4);
	if (p.x <= -half_x || p.x >= half_x || p.y <= -half_y || p.y >= half_y)
		return (NULL);
	return (object->img_data
		+ (((*win_prop)->height / 8 - (p.y * object->scale))
			* object->line_size)
		+ (((p.x) + (*win_prop)->width / 8) * object->bytes_pp));
}

static void	handle_s(t_win_prop **win_prop,
	t_map_prop **map_prop, t_vec2 *p, int height)
{
	int	x;
	int	y;

	x = (*p).x;
	y = (*p).y;
	if ((*win_prop)->s_down == 0)
	{
		(*p).x = (int)round(x * cos((*map_prop)->grades * M_PI / 200.0)
				- y * sin((*map_prop)->grades * M_PI / 200.0))
			+ (*win_prop)->offset_x;
		(*p).y = (int)round(x * sin((*map_prop)->grades * M_PI / 200.0)
				+ y * cos((*map_prop)->grades * M_PI / 200.0))
			- (*win_prop)->offset_y;
	}
	else
	{
		(*p).x = (int)round(x * cos(0) - y * sin(0))
			+ (*win_prop)->sphere_correction_x;
		(*p).y = (int)round(x * sin(0) + y * cos(0))
			+ height / 2 * (*win_prop)->scale;
	}
}

static	void	handle_a_s(t_win_prop **win_prop, t_map_prop **map_prop,
	t_vec2 *p, t_vec2 width_height)
{
	int		height;
	int		width;
	t_vec2	w_h;

	width = width_height.x;
	height = width_height.y;
	if ((*win_prop)->a_down == 1 && (*win_prop)->s_down == 0)
	{
		(*p).x = (*p).x + perspective_offset_x(win_prop,
				(*p).x, (*p).y, height);
		(*p).y = (*p).y + perspective_offset_y(map_prop, height);
	}
	if ((*win_prop)->s_down == 1)
	{
		w_h.x = width * (*win_prop)->scale;
		w_h.y = height * (*win_prop)->scale;
		(*p) = map_to_sphere((*p), w_h, height
				/ 2 * (*win_prop)->scale, height / 2 * (*win_prop)->scale);
	}
	if ((*win_prop)->s_down == 1 && (*win_prop)->s_down == 1)
	{
		(*p).x = (*p).x + (*win_prop)->offset_x;
		(*p).y = (*p).y - (*win_prop)->offset_y;
	}
}

unsigned char	*transformed_px(t_map_prop **map_prop, int width,
	int height, t_win_prop **win_prop)
{
	int		half_x;
	int		half_y;
	t_vec2	p;
	t_vec2	width_height;

	width_height.x = width;
	width_height.y = height;
	p.x = ((*map_prop)->width * (*win_prop)->scale - (*win_prop)->width
			/ 2) + centering_offset_x(win_prop, width);
	p.y = -((*map_prop)->height * (*win_prop)->scale - (*win_prop)->height
			/ 2) - centering_offset_y(win_prop, height);
	half_x = (*win_prop)->width / 2;
	half_y = (*win_prop)->height / 2;
	handle_s(win_prop, map_prop, &p, height);
	handle_a_s(win_prop, map_prop, &p, width_height);
	if (p.x <= -half_x || p.x >= half_x
		|| p.y <= -half_y || p.y >= half_y)
		return (NULL);
	return ((*map_prop)->img_data
		+ (((*win_prop)->height / 2 - (p.y)) * (*map_prop)->line_size)
		+ (((p.x) + (*win_prop)->width / 2) * (*map_prop)->bytes_pp));
}

t_vec2	map_to_sphere(t_vec2 p, t_vec2 w_h,
	int radiusX, int radiusY)
{
	t_vec2	out;
	float	phi;

	phi = M_PI * (((float)p.y / (float)w_h.y) - 0.5f);
	out.x = (int)((cosf(phi) * sinf(2.0f * M_PI * (((float)p.x / (float)w_h.x)
						- 0.5f))) * radiusX);
	out.y = (int)(sinf(phi) * radiusY);
	return (out);
}
