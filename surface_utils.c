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
	t_size s, t_win_prop **win_prop)
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
	w_h.x = s.width * 1 / 4;
	w_h.y = s.height * 1 / 4;
	p = map_to_sphere(p, w_h, s.height / 2 * object->scale
			/ 4, s.height / 2 * 1 / 4);
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
	t_vec2 *p, t_size s)
{
	t_vec2	w_h;

	if ((*win_prop)->a_down == 1 && (*win_prop)->s_down == 0)
	{
		(*p).x = (*p).x + perspective_offset_x(win_prop,
				(*p).x, (*p).y, s.height);
		(*p).y = (*p).y + perspective_offset_y(map_prop, s.height);
	}
	if ((*win_prop)->s_down == 1)
	{
		w_h.x = s.width * (*win_prop)->scale;
		w_h.y = s.height * (*win_prop)->scale;
		(*p) = map_to_sphere((*p), w_h, s.height
				/ 2 * (*win_prop)->scale, s.height / 2 * (*win_prop)->scale);
	}
	if ((*win_prop)->s_down == 1 && (*win_prop)->s_down == 1)
	{
		(*p).x = (*p).x + (*win_prop)->offset_x;
		(*p).y = (*p).y - (*win_prop)->offset_y;
	}
}

unsigned char	*transformed_px(t_vars **vars, t_size s, int map_height)
{
	int		half_x;
	int		half_y;
	t_vec2	p;

	p.x = ((*vars)->map_prop->width * (*vars)->win_prop->scale
			- (*vars)->win_prop->width / 2);
	p.y = -((*vars)->map_prop->height * (*vars)->win_prop->scale
			- (*vars)->win_prop->height / 2);
	p.x = p.x + centering_offset_x(&((*vars)->win_prop), s.width);
	p.y = p.y - centering_offset_y(&((*vars)->win_prop), s.height);
	half_x = (*vars)->win_prop->width / 2;
	half_y = (*vars)->win_prop->height / 2;
	handle_s(&((*vars)->win_prop), &((*vars)->map_prop), &p, s.height);
	handle_a_s(&((*vars)->win_prop), &((*vars)->map_prop), &p, s);
	if (p.x <= -half_x || p.x >= half_x
		|| p.y <= -half_y || p.y >= half_y)
		return (NULL);
	return ((*vars)->map_prop->img_data
		+ (((*vars)->win_prop->height / 2 - (p.y))
			* (*vars)->map_prop->line_size)
		+ (((p.x) + (*vars)->win_prop->width / 2) * (*vars)->map_prop->bytes_pp)
		+ offset_z((&(*vars)->win_prop), map_height, (&(*vars)->map_prop)));
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
