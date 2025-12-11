/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:46:35 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/10 13:46:37 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	create_color(unsigned char r,
			unsigned char g, unsigned char b)
{
	unsigned char	a;

	a = 255;
	return (((unsigned int)a << 24)
		| ((unsigned int)r << 16)
		| ((unsigned int)g << 8)
		| ((unsigned int)b));
}

static int	clamp_height(int height)
{
	if (height < 0)
		return (0);
	if (height > 1000)
		return (1000);
	return (height);
}

void	set_color_red(unsigned char *pixel, int map_height,
			t_win_prop **win_prop, int lvl)
{
	float			t;
	unsigned int	color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	map_height = (int)((*win_prop)->color_scaler * map_height);
	map_height = clamp_height(map_height);
	t = (float)map_height / 1000.0f;
	r = 255;
	g = (unsigned char)(255 * (1.0f - t));
	b = (unsigned char)(255 * (1.0f - t));
	color = create_color(r, g, b);
	if ((*win_prop)->b_down == 1)
		*(unsigned int *)pixel = brighten_color(color, lvl);
	else
		*(unsigned int *)pixel = color;
}

void	set_color_green(unsigned char *pixel, int map_height,
			t_win_prop **win_prop, int lvl)
{
	float			t;
	unsigned int	color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	map_height = (int)((*win_prop)->color_scaler * map_height);
	map_height = clamp_height(map_height);
	t = (float)map_height / 1000.0f;
	r = (unsigned char)(255 * (1.0f - t));
	g = 255;
	b = (unsigned char)(255 * (1.0f - t));
	color = create_color(r, g, b);
	if ((*win_prop)->b_down == 1)
		*(unsigned int *)pixel = brighten_color(color, lvl);
	else
		*(unsigned int *)pixel = color;
}

void	set_color_blue(unsigned char *pixel, int map_height,
			t_win_prop **win_prop, int lvl)
{
	float			t;
	unsigned int	color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	map_height = (int)((*win_prop)->color_scaler * map_height);
	map_height = clamp_height(map_height);
	t = (float)map_height / 1000.0f;
	r = (unsigned char)(255 * (1.0f - t));
	g = (unsigned char)(255 * (1.0f - t));
	b = 255;
	color = create_color(r, g, b);
	if ((*win_prop)->b_down == 1)
		*(unsigned int *)pixel = brighten_color(color, lvl);
	else
		*(unsigned int *)pixel = color;
}
