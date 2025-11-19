/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:05:34 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/11 12:05:35 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	offset_z(int multiplier, int map_height, t_map_prop **map_prop)
{
	return -(map_height/multiplier*(*map_prop)->bytes_pp
			+ (map_height/multiplier)*(*map_prop)->line_size*(*map_prop)->bytes_pp);
}

unsigned char	*rotated_px(unsigned char *pixel, t_map_prop **map_prop, int width, int height, t_win_prop **win_prop)
{
	
	int diff = (pixel - (*map_prop)->img_data)/(*map_prop)->bytes_pp;
	int divider = (*map_prop)->line_size/(*map_prop)->bytes_pp*(*win_prop)->scale;
	int y = height*(*win_prop)->scale/2-diff/divider*(*win_prop)->scale;
	int x = -((*map_prop)->line_size/(*map_prop)->bytes_pp/2-(diff - (height*(*win_prop)->scale/2-y)/(*win_prop)->scale*divider));
	double angle_rad = (*map_prop)->grades * M_PI / 200.0;
	
	
	double cosA = cos(angle_rad);
	double sinA = sin(angle_rad);

	double nx = x * cosA - y * sinA;
	double ny = x * sinA + y * cosA;

	int out_x = (int)round(nx);
	int out_y = (int)round(ny);
	
	if ((*map_prop)->width%100==0 && (*map_prop)->height%100==0)
	{
		ft_printf("Stare koordynaty: (%d, %d)\n", x, y);
		ft_printf("Kat obrotu: %d stopni\n", (*map_prop)->grades);
		ft_printf("Nowe koordynaty: (%d, %d)\n\n", out_x, out_y);
	}

	int diff_y = (height * (*win_prop)->scale / 2 - out_y);
	diff_y = (diff_y * divider) / (*win_prop)->scale;

	int diff_x = out_x + divider/2;

	int out_diff = diff_y + diff_x
		+ (*win_prop)->width/2 - (width*(*win_prop)->scale/2)+(*win_prop)->scale/4 // wysrodkowanie x
		+ ((*win_prop)->height/2 - height*(*win_prop)->scale/2 + (*win_prop)->scale/2) * (*win_prop)->width;

	unsigned char *out_pixel = 
    	(*map_prop)->img_data + out_diff * (*map_prop)->bytes_pp
    	 - (*map_prop)->line_size/2*((*win_prop)->scale-1) + (*win_prop)->scale/4*4
    	 ;
	if ((*map_prop)->width%100==0 && (*map_prop)->height%100==0)
	{
    		ft_printf("stary %p, nowy %p, roznica %d\n", pixel, out_pixel, pixel-out_pixel); 
	}

    	return (out_pixel);
}

int	line_print(char **line, t_map_prop **map_prop, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int width;
	int map_height;
	int scale;
	
	width = (*map_prop)->width;
	(*map_prop)->width = 0;
	while (line[(*map_prop)->width])
	{
		map_height = ft_atoi(line[(*map_prop)->width]);
		pixel = (*map_prop)->img_data
			+ (*map_prop)->width * (*map_prop)->bytes_pp * (*win_prop)->scale
			+ (*map_prop)->height * (*map_prop)->line_size * (*win_prop)->scale;
		pixel = rotated_px(pixel, map_prop, width, height, win_prop)
			+ offset_z(2500, map_height, map_prop);
		set_hipsometric_color(pixel, map_height, map_prop, win_prop);
		(*map_prop)->width++;
	}
	return (0);
}

int	draw(char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;
	int	height;

	if ((*win_prop)->width/(*map_prop)->width < (*win_prop)->height/(*map_prop)->height)
		(*win_prop)->scale = (*win_prop)->width/((*map_prop)->width);
	else
		(*win_prop)->scale = (*win_prop)->height/((*map_prop)->height);
	//(*win_prop)->scale = (*win_prop)->scale/2;
	height = (*map_prop)->height;
	(*map_prop)->height = 0;
	while (file_split[(*map_prop)->height] != NULL)
	{
		line = ft_split(file_split[(*map_prop)->height], ' ');
		if (!line)
			return (-1);
		line_print(line, map_prop, win_prop, height);
		free_mlx(line, NULL, NULL);
		(*map_prop)->height++;
	}
	return (0);
}

int mouse_press(int button, int x, int y, t_win_prop *win)
{
	if (button == 1)
	{
		win->mouse_down = 1;
		win->last_x = x;
		win->last_y = y;
	}
	return (0);
}


int mouse_release(int button, int x, int y, t_win_prop *win)
{
	if (button == 1)
		win->mouse_down = 0;
	return (0);
}


int mouse_move(int x, int y, t_win_prop *win, t_map_prop *map)
{
	if (win->mouse_down)
	{
		int dx = x - win->last_x;
		int dy = y - win->last_y;

		win->offset_x += dx;
       		win->offset_y += dy;
		//ft_printf("Dragged by dx=%d, dy=%d\n", dx, dy);

		win->last_x = x;
		win->last_y = y;
		
		//draw(win->file_split, map, win);
	}
	return (0);
}


int	mouse_actions(void *win, t_win_prop *win_prop)
{
	mlx_hook(win, 4, 1L<<2, mouse_press, win_prop);
	mlx_hook(win, 5, 1L<<3, mouse_release, win_prop);
	mlx_hook(win, 6, 1L<<6, mouse_move, win_prop);
}

int	fdf(char *filename)
{
	t_vars		*vars;
	t_map_prop	*map_prop;
	t_win_prop	*win_prop;

	if (init_all(&win_prop, &vars, &map_prop, filename) < 0)
		return (-1);
	if (set_res(win_prop->file_split, &map_prop) < 0)
		return (-1);
	draw(win_prop->file_split, &map_prop, &win_prop);
	//2D
	//set_padding(&win_prop, &map_prop);
	///if (img_gen(file_split, &map_prop, &win_prop) < 0)
		//return (-1);
	free_mlx(win_prop->file_split, &win_prop, &map_prop);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mouse_actions(vars->win, win_prop);

	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	fdf(argv[1]);
	return (0);
}
