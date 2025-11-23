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

int centering_offset_y(t_win_prop **win_prop, int height)
{
        int offset_y = ((*win_prop)->height - height * (*win_prop)->scale);
        return offset_y/2;
}

int centering_offset_x(t_win_prop **win_prop, int width)
{
        int offset_x = ((*win_prop)->width  - width  * (*win_prop)->scale);
        return offset_x/2;
}

int	perspective_offset_x(t_win_prop **win_prop, int out_x, int out_y, int height)
{

	int offset_x = sqrt(out_x*out_x)*(height-out_y*3)/(*win_prop)->height/2;
	//if (out_x%50 == 0 && out_y%50 == 0)
		//ft_printf("%d %d %d\n", (*map_prop)->height*(*win_prop)->scale, out_x, out_y);
	if (out_x<0)
		return -offset_x;
	return offset_x;
}
int perspective_offset_y(t_map_prop **map_prop, int height)
{
	return -((height-(*map_prop)->height)/10);
}

typedef struct {
	int x, y;
} Vec2;

Vec2 map_to_sphere_2D(int px, int py, int width, int height,
					  int radiusX, int radiusY)
{
	// mapowanie pikseli do UV (0..1)
	float u = (float)px / (float)width;
	float v = (float)py / (float)height;

	// długość i szerokość geograficzna
	float lambda = 2.0f * M_PI * (u - 0.5f);   // longitude
	float phi    = M_PI * (v - 0.5f);          // latitude

	// rzutowanie ortograficzne na 2D
	float xf = cosf(phi) * sinf(lambda);
	float yf = sinf(phi);

	Vec2 out;
	out.x = (int)(xf * radiusX);
	out.y = (int)(yf * radiusY);

	return out;
}

unsigned char	*rotated_px(t_map_prop **map_prop, int width, int height, t_win_prop **win_prop)
{
	int half_x;
	int half_y;
	int out_x;
	int out_y;
	Vec2 p;

	out_x = ((*map_prop)->width*(*win_prop)->scale-(*win_prop)->width/2) + centering_offset_x(win_prop, width);
	out_y = -((*map_prop)->height*(*win_prop)->scale-(*win_prop)->height/2) - centering_offset_y(win_prop, height);
	half_x = (*win_prop)->width/2;
	half_y = (*win_prop)->height/2;
	if ((*win_prop)->s_down == 0) {
		out_x = (int)round(out_x * cos((*map_prop)->grades * M_PI / 200.0) - out_y * sin((*map_prop)->grades * M_PI / 200.0)) + (*win_prop)->offset_x;
		out_y = (int)round(out_x * sin((*map_prop)->grades * M_PI / 200.0) + out_y * cos((*map_prop)->grades * M_PI / 200.0)) - (*win_prop)->offset_y;
	}
	else {
		out_x = (int)round(out_x * cos(0) - out_y * sin(0))+ (*win_prop)->sphere_correction_x;
		out_y = (int)round(out_x * sin(0) + out_y * cos(0))+ height/2*(*win_prop)->scale;
	}
	if ((*win_prop)->a_down == 1 && (*win_prop)->s_down == 0) {
		out_x = out_x + perspective_offset_x(win_prop, out_x, out_y, height);
		out_y = out_y + perspective_offset_y(map_prop, height);
	}
	if ((*win_prop)->s_down == 1) {
		p = map_to_sphere_2D(out_x, out_y,
			  width*(*win_prop)->scale, height*(*win_prop)->scale,
			  height/2*(*win_prop)->scale, height/2*(*win_prop)->scale);
		out_x = p.x;
		out_y = p.y;
	}
	if ((*win_prop)->s_down == 1 && (*win_prop)->s_down == 1) {
		out_x = out_x + (*win_prop)->offset_x;
		out_y = out_y - (*win_prop)->offset_y;
	}
	if (out_x <= -half_x || out_x >= half_x-10 || out_y <= -half_y+10 || out_y >= half_y)
       	return (NULL);
    return ((*map_prop)->img_data
			+ ( ((*win_prop)->height/2 - (out_y)) * (*map_prop)->line_size )
			+ ( ((out_x) + (*win_prop)->width/2) * (*map_prop)->bytes_pp ));
}

unsigned char	*rotated_px_object(t_object *object, int width, int height, t_win_prop **win_prop)
{
	int half_x;
	int half_y;
	int out_x;
	int out_y;
	Vec2 p;

	object->grades = 0;
	half_x = (*win_prop)->width/2;
	half_y = (*win_prop)->height/2;
	out_x = (object->width*object->scale/4-(*win_prop)->width/2);
	out_y = -(object->height*object->scale/4-(*win_prop)->height/2);

	out_x = (int)round(out_x * cos(object->grades * M_PI / 200.0) - out_y * sin(object->grades * M_PI / 200.0)) + object->offset_x;
	out_y = (int)round(out_x * sin(object->grades * M_PI / 200.0) + out_y * cos(object->grades * M_PI / 200.0));

	p = map_to_sphere_2D(out_x, out_y,
					  width*1/4, height*1/4,
					  height/2*object->scale/4, height/2*1/4);
	out_x = p.x;
	out_y = p.y;

	if (out_x <= -half_x || out_x >= half_x || out_y <= -half_y || out_y >= half_y)
		return (NULL);
	return (object->img_data
			+ ( ((*win_prop)->height/8 - (out_y*object->scale)) * object->line_size )
			+ ( ((out_x) + (*win_prop)->width/8) * object->bytes_pp ));
}

char pixel_in_screen(unsigned char *pixel, t_win_prop **win_prop, t_map_prop **map_prop)
{
    unsigned char *start = (*map_prop)->img_data;
    unsigned char *end = start + (*win_prop)->height * (*win_prop)->height*8;
    if (pixel < start || pixel >= end)
		return (NULL);
	return ('t');
}

char pixel_in_screen_object(unsigned char *pixel, t_win_prop **win_prop, t_object **object)
{
	unsigned char *start = (*object)->img_data;
	unsigned char *end = start + (*win_prop)->height * (*win_prop)->height/2;
	if (pixel < start || pixel >= end)
		return (NULL);
	return ('t');
}


int	line_print(char **line, t_map_prop **map_prop, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int width;
	int map_height;
	
	width = (*map_prop)->width;
	(*map_prop)->width = 0;
	while (line[(*map_prop)->width])
	{
		map_height = ft_atoi(line[(*map_prop)->width]);
		/*pixel = (*map_prop)->img_data
			+ (*map_prop)->width * (*map_prop)->bytes_pp * (*win_prop)->scale
			+ (*map_prop)->height * (*map_prop)->line_size * (*win_prop)->scale;*/
		pixel = rotated_px(map_prop, width, height, win_prop)
			//+ offset_z(1000/(*win_prop)->scale, map_height, map_prop)
			;
		if (pixel && pixel_in_screen(pixel, win_prop, map_prop)) {
			if ((*win_prop)->c_down == 1)
				set_moon_color(pixel, map_height);
			if ((*win_prop)->c_down == 0)
				set_hipsometric_color(pixel, map_height, map_prop, win_prop);
		}
		(*map_prop)->width++;
	}
	return (0);
}

int	draw(char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;
	int	height;

	if ((*win_prop)->scale == 0)
	{
		if ((*win_prop)->width/(*map_prop)->width < (*win_prop)->height/(*map_prop)->height)
			(*win_prop)->scale = (*win_prop)->width/((*map_prop)->width);
	    else
			(*win_prop)->scale = (*win_prop)->height/((*map_prop)->height);
        }
	if ((*win_prop)->scale == 0)
		(*win_prop)->scale = 1;
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
int centering_offset_y_object(t_object *object, int height)
{
	int offset_y = (object->height - height * object->scale);
	return offset_y/2;
}

int centering_offset_x_object(t_object *object, int width)
{
	int offset_x = (object->width  - width  * object->scale);
	return offset_x/2;
}


int	line_print_object(char **line, t_object *object, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int width;
	int map_height;

	map_height = 0;
	width = object->width;
	object->width = 0;
	while (line[object->width])
	{
		map_height = ft_atoi(line[object->width]);
		/*pixel = object->img_data
			+ object->width * object->bytes_pp * object->scale/4
			+ object->height * object->line_size * object->scale/4;*/
		pixel = rotated_px_object(object, width, height, win_prop);
		// 	+ offset_z(1000/(*win_prop)->scale, map_height, map_prop)
		// 	;
		 if (pixel && pixel_in_screen_object(pixel, win_prop, &object))
		 	set_moon_color(pixel,map_height);
		object->width++;
	}
	return (0);
}

int draw_object(t_object *object, t_win_prop **win_prop) {
	char	**line;
	int	height;
	if (object->scale == 0)
	{
		if ((*win_prop)->width/object->width < (*win_prop)->height/object->height)
			object->scale = (*win_prop)->width/(object->width);
		else
			object->scale = (*win_prop)->height/(object->height);
	}
	if (object->scale == 0)
		object->scale = 1;
	height = object->height;
	object->height = 0;
	while (object->file_split[object->height] != NULL)
	{
		line = ft_split(object->file_split[object->height], ' ');
		if (!line)
			return (-1);
		line_print_object(line, object, win_prop, height);
		free_mlx(line, NULL, NULL);
		object->height++;
	}
	return (0);
}

void redraw (t_vars **vars) {
	mlx_destroy_image((*vars)->mlx, (*vars)->img);
	(*vars)->img = mlx_new_image((*vars)->mlx,
								 (*vars)->win_prop->width,
								 (*vars)->win_prop->height);
	draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
	mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img, 400, 0);
}

void redraw_object (t_vars **vars) {
	if ((*vars)->object) {
		mlx_destroy_image((*vars)->mlx, (*vars)->object->img);
		(*vars)->object->img = mlx_new_image((*vars)->mlx, (*vars)->win_prop->width/4, (*vars)->win_prop->height/4);
		draw_object((*vars)->object, &(*vars)->win_prop);
		mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->object->img,0, 0);
	}
}

int mouse_press(int button, int x, int y, void *param)
{
    t_vars **vars = (t_vars **)param;
	if (button == 1)
	{
		(*vars)->win_prop->mouse_down = 1;
		(*vars)->win_prop->last_x = x;
		(*vars)->win_prop->last_y = y;
	}
	if ((*vars)->win_prop->ctrl_down && (button == 4 || button == 5))
    {
        int delta_angle = (button == 4) ? 5 : -5;
        (*vars)->map_prop->grades =
            ((*vars)->map_prop->grades + delta_angle + 400) % 400;
        	redraw(vars);
			redraw_object(vars);
        return (0); 
    }

	if ((button == 4 || button == 5 ) &&
        !(*vars)->win_prop->ctrl_down)
	{
		if (button == 4) {
			if ((*vars)->object && (*vars)->win_prop->x_down == 1)
				(*vars)->object->scale++;
			else
				(*vars)->win_prop->scale++;
		}
		else {
			if ((*vars)->object && (*vars)->win_prop->x_down == 1 && (*vars)->object->scale > 1)
				(*vars)->object->scale--;
			else if ((*vars)->win_prop->x_down == 0 && (*vars)->win_prop->scale > 1)
			(*vars)->win_prop->scale--;
		}
		redraw(vars);
		redraw_object(vars);
	}
	return (0);
}

int key_press(int keycode, void *param)
{
    t_vars **vars;

	vars = (t_vars **)param;

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
    if (keycode == 65507 )
        (*vars)->win_prop->ctrl_down = 1;
	redraw(vars);
	redraw_object(vars);
    return (0);
}

int key_release(int keycode, void *param)
{
    t_vars **vars = (t_vars **)param;

    if (keycode == 65507)
        (*vars)->win_prop->ctrl_down = 0;
    return (0);
}


int mouse_release(int button, int x, int y, void *param)
{
    t_vars **vars = (t_vars **)param;

	if (button == 1)
		(*vars)->win_prop->mouse_down = 0;
	return (0);
}

void move_correction(t_vars **vars, int dx, int dy) {
	if ((*vars)->win_prop->w_down) {
		(*vars)->win_prop->sphere_correction_x += dx;
		(*vars)->win_prop->sphere_correction_y += dy;
	}
	else {
		(*vars)->win_prop->offset_x += dx;
		(*vars)->win_prop->offset_y += dy;
	}
}

int mouse_move(int x, int y, void *param)
{
    t_vars **vars;
	int dx;
	int dy;

	vars = (t_vars **)param;
	dx = x - (*vars)->win_prop->last_x;
	dy = y - (*vars)->win_prop->last_y;
    if ((*vars)->win_prop->mouse_down)
    {
        if ( dx>25 || dy > 25|| dx< -25 || dy < -25)
        {
        	move_correction(vars, dx, dy);
        	(*vars)->win_prop->last_x = x;
        	(*vars)->win_prop->last_y = y;
			redraw(vars);
        	if ((*vars)->object && (*vars)->object->img) {
        		(*vars)->object->offset_x += dx;
        		(*vars)->object->offset_y += dy;
        		(*vars)->object->last_x = x;
        		(*vars)->object->last_y = y;
        		redraw_object(vars);
        	}
        }
    }
	return (0);
}

int	mouse_actions(t_vars **vars)
{
	mlx_hook((*vars)->win, 4, 1L<<2, mouse_press, vars);
	mlx_hook((*vars)->win, 5, 1L<<3, mouse_release, vars);
	mlx_hook((*vars)->win, 6, 1L<<6, mouse_move, vars);
	mlx_hook((*vars)->win, 2, 1L<<0, key_press, vars);
	mlx_hook((*vars)->win, 3, 1L<<1, key_release, vars);
	return (0);
}

int	globe_move(void *param) {
	t_vars **vars;

	vars = (t_vars **)param;
	if ((*vars)->win_prop->q_down) {
		usleep(50000);
		(*vars)->win_prop->sphere_correction_x += 1;
		redraw(vars);
		if ((*vars)->object) {
			(*vars)->object->offset_x += 1;
			redraw_object(vars);
		}
	}
}

int proceed_second_parameter (t_vars **vars, char *filename2)
{
	t_object	*moon;

	if (filename2 != NULL) {
		init_object(vars, &moon, filename2);
		if (set_res_object(moon) < 0)
			return (-1);
		draw_object(moon, &(*vars)->win_prop);
		mlx_put_image_to_window((*vars)->mlx, (*vars)->win, moon->img, 0, 0);
	}
	else
		(*vars)->object = NULL;
	return (0);
}

int	fdf(char *filename, char *filename2)
{
	t_vars		*vars;
	t_map_prop	*map_prop;
	t_win_prop	*win_prop;

	if (init_all(&win_prop, &vars, &map_prop, filename) < 0 ||
		set_res(win_prop->file_split, &map_prop) < 0 ||
		draw(win_prop->file_split, &map_prop, &win_prop) < 0)
		return (-1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 400, 0);
	if (proceed_second_parameter(&vars, filename2) < 0)
		return (-1);
	mouse_actions(&vars);
	mlx_loop_hook(vars->mlx, globe_move, &vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		fdf(argv[1], NULL);
	if (argc == 3)
		fdf(argv[1], argv[2]);
	return (0);
}
