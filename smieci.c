/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smieci.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:44:03 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/19 11:44:04 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	pixel_in_range_if_zero_grades(unsigned char *pixel, t_map_prop **map_prop, t_win_prop **win_prop)
{	
	if (pixel >= (*map_prop)->img_data
		&& pixel < (*map_prop)->img_data + (*map_prop)->line_size * (*win_prop)->height
		&& (*map_prop)->width
		*(*win_prop)->scale
		< (*win_prop)->width
            	)
		return ('t');
	return (NULL);
}

char	pixel_out(unsigned char *pixel, t_map_prop **map_prop)
{
	static unsigned char *prev_px = NULL;
	static int prev_height = 0;
	if ((*map_prop)->height > prev_height)
		prev_px = NULL;
	if (!prev_height || (*map_prop)->height > prev_height)
		prev_height = (*map_prop)->height;
	if (!prev_px)
		prev_px = pixel;
	if (((pixel - (*map_prop)->img_data)%(*map_prop)->line_size) < ((prev_px - (*map_prop)->img_data)%(*map_prop)->line_size))
		return ('t');
	return (NULL);
}

void	pix_ver_corr(char **pixel, t_map_prop **map_prop, int scale)
{
	if ((*map_prop)->grades > 0 && (*map_prop)->grades <= 50)
	{
		if (scale%(50/(*map_prop)->grades)==0)
			(*pixel) = (*pixel) + (*map_prop)->line_size;
	}
	else if ((*map_prop)->grades > 50 && (*map_prop)->grades <= 100)
	{
		(*pixel) = (*pixel) + (*map_prop)->line_size;
		if (scale%(150/(*map_prop)->grades)==0)
			(*pixel) = (*pixel) + (*map_prop)->line_size;
	}
}

void	pix_hor_corr(char **pixel, t_map_prop **map_prop, int scale)
{
	if ((*map_prop)->grades > 0 && (*map_prop)->grades <= 50)
	{
		if ((*map_prop)->grades > 0 && scale%(50/(*map_prop)->grades)==0)
			(*pixel) = (*pixel) - (*map_prop)->bytes_pp;
	}
	else if ((*map_prop)->grades > 50 && (*map_prop)->grades <= 100)
	{
		(*pixel) = (*pixel) - (*map_prop)->bytes_pp;
		if (scale%(150/((*map_prop)->grades))==0)
			(*pixel) = (*pixel) - (*map_prop)->bytes_pp;
	}
}

void	draw_lines(int map_height, unsigned char *pixel, t_map_prop **map_prop, t_win_prop **win_prop)
{
	int scale;
	unsigned char	*temp_pixel;
	int i = 0;
	int j = 0;
	
	scale = (*win_prop)->scale;
	temp_pixel = pixel;
	while (--scale > 0)
	{
		pixel = pixel + (*map_prop)->bytes_pp;
		pix_ver_corr(&pixel, map_prop, scale);
		set_hipsometric_color(pixel, map_height, map_prop, win_prop);
	}
	scale = (*win_prop)->scale;
	pixel = temp_pixel;
	while (scale-- > 0)
	{
		pixel = pixel + (*map_prop)->line_size;
		pix_hor_corr(&pixel, map_prop, scale);
		set_hipsometric_color(pixel, map_height, map_prop, win_prop);
	}
}

int	offset_y_only_for_ninety_degrees(int height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	return 
		(
			(
				(*map_prop)->width * (*win_prop)->scale
			)
			/
			(*map_prop)->bytes_pp
		)
			*(*map_prop)->bytes_pp*(*map_prop)->grades/50 * (*map_prop)->line_size
			
			- (*win_prop)->scale * (*map_prop)->bytes_pp * (*map_prop)->width
			- (*win_prop)->scale * (*map_prop)->line_size * (*map_prop)->width
		;	
}

int	offset_x_only_for_ninety_degrees(int height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	return 
		(
			(
				(height-(*map_prop)->height) * (*win_prop)->scale - (*win_prop)->scale
			)
			/
			(*map_prop)->bytes_pp
		) 
		*(*map_prop)->bytes_pp
		*((*map_prop)->grades*4)
		/50
		
		+(height-(*map_prop)->height)*(*map_prop)->grades*(*map_prop)->line_size/2
		-(height-(*map_prop)->height) * (*map_prop)->bytes_pp * (*win_prop)->scale
		+(*map_prop)->line_size*(height-(*map_prop)->height)*(*map_prop)->bytes_pp/2
		- (*map_prop)->line_size * ((*win_prop)->height)/2
		-(*map_prop)->line_size*50
		+(*map_prop)->line_size/2
		-(*map_prop)->line_size/4
		;
}

int	offset_y_works_but_makes_it_bigger(int height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	return 
		(
			(
				(*map_prop)->width * (*win_prop)->scale
			)
			/
			(*map_prop)->bytes_pp
		)
			*(*map_prop)->bytes_pp*(*map_prop)->grades/50 * (*map_prop)->line_size
			;
}

int	offset_x_works_but_makes_it_bigger(int height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	return 
		(
			(
				(height-(*map_prop)->height) * (*win_prop)->scale - (*win_prop)->scale
			)
			/
			(*map_prop)->bytes_pp
		) 
		*(*map_prop)->bytes_pp
		*((*map_prop)->grades*4)
		/50
		;
}

int	offset_x_based_on_sinus(int width, int height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	return
		((int)(
		(1.0 - (double)(*map_prop)->width/(double)width)
		*(double)((width*(*map_prop)->bytes_pp*(*map_prop)->bytes_pp)
		))
		*(*map_prop)->grades/100
		/16)
		*(*win_prop)->scale
		*(*map_prop)->bytes_pp
		-((width-1)*(*win_prop)->scale/(100/(*map_prop)->grades))*((*map_prop)->height)/ height
		*(*map_prop)->bytes_pp
		;
}
