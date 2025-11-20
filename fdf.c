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
unsigned char	*rotated_px(unsigned char *pixel, t_map_prop **map_prop, int width, int height, t_win_prop **win_prop)
{
        int x;
        int y;
        int half_x;
        int out_x;
        int out_y;

	x = ((*map_prop)->width*(*win_prop)->scale-(*win_prop)->width/2) + centering_offset_x(win_prop, width);
	y = -((*map_prop)->height*(*win_prop)->scale-(*win_prop)->height/2) - centering_offset_y(win_prop, height);
        half_x = (*win_prop)->width/2;
        //int x = (((pixel - (*map_prop)->img_data) % (*map_prop)->line_size) / (*map_prop)->bytes_pp
              //- (*win_prop)->width / 2) + offset_x / 2;

        //int y = ((*win_prop)->height / 2
              //- ((pixel - (*map_prop)->img_data) / (*map_prop)->line_size)) - offset_y / 2;
	out_x = (int)round(x * cos((*map_prop)->grades * M_PI / 200.0) - y * sin((*map_prop)->grades * M_PI / 200.0));
	out_y = (int)round(x * sin((*map_prop)->grades * M_PI / 200.0) + y * cos((*map_prop)->grades * M_PI / 200.0));
        if (out_x <= -half_x || out_x >= half_x)
          return (NULL);
    	return ((*map_prop)->img_data
	+ ( ((*win_prop)->height/2 - (out_y)) * (*map_prop)->line_size )
	+ ( ((out_x) + (*win_prop)->width/2) * (*map_prop)->bytes_pp ));
}

char pixel_in_screen(unsigned char *pixel, t_win_prop **win_prop, t_map_prop **map_prop, int width, int height)
{
    unsigned char *start = (*map_prop)->img_data;
    unsigned char *end = start + (*win_prop)->height * (*win_prop)->height*8;
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
		pixel = (*map_prop)->img_data
			+ (*map_prop)->width * (*map_prop)->bytes_pp * (*win_prop)->scale
			+ (*map_prop)->height * (*map_prop)->line_size * (*win_prop)->scale;
		pixel = rotated_px(pixel, map_prop, width, height, win_prop)
			+ offset_z(20, map_height, map_prop)
			;
                if (pixel && pixel_in_screen(pixel, win_prop, map_prop, width, height))
		  set_hipsometric_color(pixel, map_height, map_prop, win_prop);
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
	//(*win_prop)->scale = 1;
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

void draw_black(t_map_prop **map_prop, t_win_prop **win_prop)
{
    int x, y;
    unsigned char *pixel;

    pixel = (*map_prop)->img_data;

  x = 0;
    while (x < 480000)
{
      *(unsigned int *)pixel = 0x00FFFFFF;
      x++;
      pixel++;
}

}

#include <string.h>
int mouse_scroll(int button, int x, int y, void *param)
{
    t_vars **vars = (t_vars **)param;

    (void)x;
    (void)y;

    if (button == 4) // scroll up
        (*vars)->win_prop->scale++;
    else if (button == 5 && (*vars)->win_prop->scale > 1) // scroll down
        (*vars)->win_prop->scale--;
    else
        return (0);

    // czyścimy obraz (potrzebne przed draw)
    //ft_printf("%d %d", (*vars)->win_prop->scale, (*vars)->win_prop->offset_y);
    // rysujemy nowy widok
    draw_black(&(*vars)->map_prop, &(*vars)->win_prop);
    //draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
    if ((*vars)->img)
		mlx_destroy_image((*vars)->mlx, (*vars)->img);
	if ((*vars)->win)
		mlx_destroy_window((*vars)->mlx, (*vars)->win);
	if ((*vars)->mlx)
	{
		mlx_destroy_display((*vars)->mlx);
		free((*vars)->mlx);
	}
free((*vars)->img);
(*vars)->img = mlx_new_image((*vars)->mlx,
			(*vars)->win_prop->width, (*vars)->win_prop->height);
    // wyświetlamy obraz
    mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                            (*vars)->win_prop->offset_x,
                            (*vars)->win_prop->offset_y);

    return (0);
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
        if (button == 4 || (button == 5 && (*vars)->win_prop->scale > 1)) // scroll up
	{
                if (button == 4)
		        (*vars)->win_prop->scale++;
                else
                        (*vars)->win_prop->scale--;
		//mlx_destroy_image((*vars)->mlx, (*vars)->img);
                //(*vars)->img = mlx_new_image((*vars)->mlx,
			//(*vars)->win_prop->width, (*vars)->win_prop->height);
                //draw_black(&(*vars)->map_prop, &(*vars)->win_prop);
                //mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                                //(*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y);
                mlx_destroy_image((*vars)->mlx, (*vars)->img);
                (*vars)->img = mlx_new_image((*vars)->mlx,
			(*vars)->win_prop->width, (*vars)->win_prop->height);
                draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
                mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                                (*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y);
                //ft_printf("%d %d %d\n", (*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y, (*vars)->win_prop->scale);
	}
	return (0);
}

int key_press(int keycode, void *param)
{
    t_vars **vars = (t_vars **)param;
    ft_printf("%d", keycode);
    if (keycode == 65507 ) // left ctrl w MLX/X11
        (*vars)->win_prop->ctrl_down = 1;
    return (0);
}

int key_release(int keycode, void *param)
{
    t_vars **vars = (t_vars **)param;

    if (keycode == 65507) // left ctrl
        (*vars)->win_prop->ctrl_down = 0;
    return (0);
}

int mouse_rotate(int x, int y, void *param)
{
    t_vars **vars = (t_vars **)param;
    t_win_prop *win = (*vars)->win_prop;
    t_map_prop *map = (*vars)->map_prop;

    // tylko jeśli LPM i Ctrl są wciśnięte
    if (win->mouse_down && win->ctrl_down)
    {
        int dx = x - win->last_x;

        // środek ekranu
        int cx = win->width / 2;
        int cy = win->height / 2;

        // odległość od środka w osi X i Y
        int dist_x = abs(x - cx);
        int dist_y = abs(y - cy);
        int max_dist = cx; // dla X, zakładamy kwadratowe okno

        // współczynnik przyspieszenia obrotu (bliżej środka -> szybciej)
        double speed = 1.0 + (double)(max_dist - dist_x) / max_dist * 4.0; // max 5x

        // zmieniamy kąt, ograniczamy do 0-399
        map->grades = (map->grades + (int)(dx * speed) + 400) % 400;

        // aktualizujemy ostatnią pozycję myszy
        win->last_x = x;
        win->last_y = y;

        // rysujemy od nowa
        mlx_destroy_image((*vars)->mlx, (*vars)->img);
        (*vars)->img = mlx_new_image((*vars)->mlx, win->width, win->height);
        draw(win->file_split, &map, &win);
        mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                                win->offset_x, win->offset_y);
    }

    return (0);
}

int mouse_release(int button, int x, int y, void *param)
{
    t_vars **vars = (t_vars **)param;
	if (button == 1)
		(*vars)->win_prop->mouse_down = 0;
	return (0);
}


int mouse_move(int x, int y, void *param)
{
    
    t_vars **vars = (t_vars **)param;
  
    if ((*vars)->win_prop->mouse_down && (*vars)->win_prop->ctrl_down)
    {
        int dx = x - (*vars)->win_prop->last_x;

        // środek ekranu
        int cx = (*vars)->win_prop->width / 2;
        int cy = (*vars)->win_prop->height / 2;

        // odległość od środka w osi X i Y
        int dist_x = abs(x - cx);
        int dist_y = abs(y - cy);
        int max_dist = cx; // dla X, zakładamy kwadratowe okno

        // współczynnik przyspieszenia obrotu (bliżej środka -> szybciej)
        double speed = 1.0 + (double)(max_dist - dist_x) / max_dist * 4.0; // max 5x

        // zmieniamy kąt, ograniczamy do 0-399
        (*vars)->map_prop->grades = ((*vars)->map_prop->grades + (int)(dx * speed) + 400) % 400;

        // aktualizujemy ostatnią pozycję myszy
        (*vars)->win_prop->last_x = x;
        (*vars)->win_prop->last_y = y;

        // rysujemy od nowa
        mlx_destroy_image((*vars)->mlx, (*vars)->img);
        (*vars)->img = mlx_new_image((*vars)->mlx, (*vars)->win_prop->width, (*vars)->win_prop->height);
        draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);
        mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                                (*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y);
    }
    else if ((*vars)->win_prop->mouse_down)
    {
        int dx = x - (*vars)->win_prop->last_x;
        int dy = y - (*vars)->win_prop->last_y;

        (*vars)->win_prop->offset_x += dx;
        (*vars)->win_prop->offset_y += dy;

        (*vars)->win_prop->last_x = x;
        (*vars)->win_prop->last_y = y;

        //ft_printf("%d %d %d", (*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y, (*vars)->win_prop->scale);
        //draw((*vars)->win_prop->file_split, &(*vars)->map_prop, &(*vars)->win_prop);

        mlx_put_image_to_window((*vars)->mlx, (*vars)->win, (*vars)->img,
                                (*vars)->win_prop->offset_x, (*vars)->win_prop->offset_y);
    }
    return (0);
}



int	mouse_actions(t_vars **vars)
{
	mlx_hook((*vars)->win, 4, 1L<<2, mouse_press, vars);
	mlx_hook((*vars)->win, 5, 1L<<3, mouse_release, vars);
	mlx_hook((*vars)->win, 6, 1L<<6, mouse_move, vars);
        mlx_hook((*vars)->win, 2, 1L<<0, key_press, vars);    // key press
        mlx_hook((*vars)->win, 3, 1L<<1, key_release, vars);  // key release
        //mlx_hook((*vars)->win, 6, 1L<<6, mouse_rotate, vars); // mouse move

	//mlx_hook((*vars)->win, 4, 1L<<2, mouse_scroll, vars);

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

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, win_prop->offset_x, win_prop->offset_y);
	mouse_actions(&vars);

	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	fdf(argv[1]);
	return (0);
}
