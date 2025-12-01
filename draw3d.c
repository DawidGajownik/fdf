/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:17:36 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 16:17:38 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	pixel_in_screen(unsigned char *pixel,
	t_win_prop **win_prop, t_map_prop **map_prop)
{
	unsigned char	*start;
	unsigned char	*end;

	start = (*map_prop)->img_data;
	end = start + (*win_prop)->height * (*win_prop)->height * 8;
	if (pixel < start || pixel >= end)
		return (NULL);
	return ('t');
}
static float distance(t_vec2 a, t_vec2 b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// callback ma postać: void put_pixel(int x, int y, void *data);
void    bresenham(t_vec2 p, t_vec2 n, t_map_prop **map_prop, t_win_prop **win_prop, int map_height_p, int map_height_n)
{
	t_vec2 p0 = p;
	float full_dist = distance(p0, n);

    int dx = abs(n.x - p.x);
    int sx = p.x < n.x ? 1 : -1;
    int dy = -abs(n.y - p.y);
    int sy = p.y < n.y ? 1 : -1;
    int err = dx + dy;
    int e2;
	unsigned char *pixel;
	int half_x = (*win_prop)->width / 2;
	int half_y = (*win_prop)->height / 2;
	int map_height;

    while (1)
    {
		if (p.x <= -half_x + 1 || p.x >= half_x - 10
			|| p.y <= -half_y || p.y >= half_y)
			return (NULL);

		float current_dist = distance(p0, p);
    	float t = full_dist == 0 ? 0 : current_dist / full_dist;

    	map_height = (int)((1.0f - t) * map_height_p + t * map_height_n);

		pixel = ((*map_prop)->img_data
		+ (((*win_prop)->height / 2 - (p.y)) * (*map_prop)->line_size)
		+ (((p.x) + (*win_prop)->width / 2) * (*map_prop)->bytes_pp));
		
		if ((*win_prop)->c_down == 1)
				set_moon_color(pixel, map_height, win_prop);
		if ((*win_prop)->c_down == 0)
				set_hipsometric_color(pixel, map_height, map_prop, win_prop);
        if (p.x == n.x && p.y == n.y)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            p.x += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            p.y += sy;
        }
    }
}


void get_coords_from_addr(
        unsigned char *addr,
        t_map_prop **map_prop,
        t_win_prop **win_prop,
        t_vec2 *p)
{
    long offset = addr - (*map_prop)->img_data;

    int row = offset / (*map_prop)->line_size;
    int col = (offset % (*map_prop)->line_size) / (*map_prop)->bytes_pp;

    (*p).y = ((*win_prop)->height / 2) - row;
    (*p).x = col - ((*win_prop)->width / 2);
}


static int	draw_line(t_map_prop **map_prop, t_win_prop **win_prop, char *pixel, unsigned char *next_pixel, int map_height, int map_height_n)
{
	t_vec2 p;
	t_vec2 n;

	get_coords_from_addr(pixel, map_prop, win_prop, &p);
	get_coords_from_addr(next_pixel, map_prop, win_prop, &n);
	bresenham(p, n, map_prop, win_prop, map_height, map_height_n);
}

void	paint_point(t_map_prop **map_prop, t_win_prop **win_prop, int map_height, t_vec2 p)
{
	unsigned char	*pixel;
	int half_x;
	int half_y;

	half_x = (*win_prop)->width / 2;
	half_y = (*win_prop)->height / 2;
	if (p.x <= -half_x + 1 || p.x >= half_x - 10
			|| p.y <= -half_y || p.y >= half_y)
			return (NULL);
		pixel = ((*map_prop)->img_data
		+ (((*win_prop)->height / 2 - (p.y)) * (*map_prop)->line_size)
		+ (((p.x) + (*win_prop)->width / 2) * (*map_prop)->bytes_pp));
		
		if ((*win_prop)->c_down == 1)
				set_moon_color(pixel, map_height, win_prop);
		if ((*win_prop)->c_down == 0)
			if ((*win_prop)->b_down == 1)
				set_hipsometric_color_brighter(pixel, map_height, map_prop, win_prop);
			else
				set_hipsometric_color(pixel, map_height, map_prop, win_prop);
}

static float  dist(t_vec2 a, t_vec2 b)
{
    float dx = (float)a.x - (float)b.x;
    float dy = (float)a.y - (float)b.y;
    return sqrtf(dx * dx + dy * dy);
}

static int    weighted_height(t_vec2 p, t_vec2 p1, t_vec2 p2, t_vec2 p3, t_vec2 p4,
                              int mh1, int mh2, int mh3, int mh4)
{
    float d1 = dist(p, p1);
    float d2 = dist(p, p2);
    float d3 = dist(p, p3);
    float d4 = dist(p, p4);

    // zabezpieczenie przed dzieleniem przez 0 – piksel idealnie trafia w punkt
    if (d1 == 0) return mh1;
    if (d2 == 0) return mh2;
    if (d3 == 0) return mh3;
    if (d4 == 0) return mh4;

    // inverse distance weights
    float w1 = 1.0f / d1;
    float w2 = 1.0f / d2;
    float w3 = 1.0f / d3;
    float w4 = 1.0f / d4;

    float sum = w1 + w2 + w3 + w4;

    float h =
        (w1 * mh1 +
         w2 * mh2 +
         w3 * mh3 +
         w4 * mh4) / sum;

    return (int)h;
}

int point_in_poly(int x, int y, t_vec2 poly[4])
{
    int inside = 0;
    for (int i = 0, j = 3; i < 4; j = i++)
    {
        int xi = poly[i].x, yi = poly[i].y;
        int xj = poly[j].x, yj = poly[j].y;

        int intersect = ((yi > y) != (yj > y)) &&
            (x < (xj - xi) * (float)(y - yi) / (float)(yj - yi + 0.00001f) + xi);

        if (intersect)
            inside = !inside;
    }
    return inside;
}


void	iterate_quad(t_map_prop **map_prop, t_win_prop **win_prop, unsigned char *px1, unsigned char *px2, unsigned char *px3, unsigned char *px4,
	int mh1, int mh2, int mh3, int mh4)
{
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int map_height;
	t_vec2 p;
	t_vec2 p1;
	t_vec2 p2;
	t_vec2 p3;
	t_vec2 p4;
	t_vec2 poly[4];


	get_coords_from_addr(px1, map_prop, win_prop, &p1);
	get_coords_from_addr(px2, map_prop, win_prop, &p2);
	get_coords_from_addr(px3, map_prop, win_prop, &p3);
	get_coords_from_addr(px4, map_prop, win_prop, &p4);
	poly[0] = p1;
	poly[1] = p2;
	poly[2] = p4;
	poly[3] = p3;
	min_x = p1.x;
	if (p2.x < min_x) min_x = p2.x;
	if (p3.x < min_x) min_x = p3.x;
	if (p4.x < min_x) min_x = p4.x;

	max_x = p1.x;
	if (p2.x > max_x) max_x = p2.x;
	if (p3.x > max_x) max_x = p3.x;
	if (p4.x > max_x) max_x = p4.x;

	min_y = p1.y;
	if (p2.y < min_y) min_y = p2.y;
	if (p3.y < min_y) min_y = p3.y;
	if (p4.y < min_y) min_y = p4.y;

	max_y = p1.y;
	if (p2.y > max_y) max_y = p2.y;
	if (p3.y > max_y) max_y = p3.y;
	if (p4.y > max_y) max_y = p4.y;

	p.y = min_y;
	while (p.y <= max_y)
	{
		p.x = min_x;
		while (p.x <= max_x)
		{
			if (point_in_poly(p.x, p.y, poly))
			{
				map_height = weighted_height(p, p1, p2, p3, p4,
                                             mh1, mh2, mh3, mh4);
				paint_point(map_prop, win_prop, map_height, p);
			}
			p.x++;
		}
		p.y++;
	}
}



static int	line_print(char **line, char **next_line, 
	t_map_prop **map_prop, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	unsigned char	*next_pixel;
	unsigned char	*next_line_pixel;
	unsigned char	*next_line_next_pixel;
	int				width;
	int				map_height;
	int				next_map_height;
	int				next_line_map_height;
	int				next_line_next_map_height;

	width = (*map_prop)->width;
	(*map_prop)->width = 0;
	while (line[(*map_prop)->width])
	{
		map_height = ft_atoi_hex(line[(*map_prop)->width]);
		pixel = transformed_px(map_prop, width, height, win_prop)
			//+ offset_z((*win_prop)->divider / (*win_prop)->scale, map_height, map_prop)
			;
		/*if (pixel && pixel_in_screen(pixel, win_prop, map_prop))
		{
			if ((*win_prop)->c_down == 1)
				set_moon_color(pixel, map_height);
			if ((*win_prop)->c_down == 0)
				set_hipsometric_color(pixel, map_height, map_prop, win_prop);
		}*/
		if (next_line && next_line[(*map_prop)->width] != NULL)
		{
			(*map_prop)->height++;
			next_line_map_height = ft_atoi_hex(next_line[(*map_prop)->width]);
			next_line_pixel = transformed_px(map_prop, width, height, win_prop)
				//+ offset_z((*win_prop)->divider / (*win_prop)->scale, next_line_map_height, map_prop)
				;
			/*if (pixel && next_line_pixel && pixel_in_screen(pixel, win_prop, map_prop) && pixel_in_screen(next_line_pixel, win_prop, map_prop))
				draw_line(map_prop, win_prop, pixel, next_line_pixel, map_height, next_line_map_height);*/
			(*map_prop)->height--;
		}
		(*map_prop)->width++;
		if (line[(*map_prop)->width])
		{
			next_map_height = ft_atoi_hex(line[(*map_prop)->width]);
			next_pixel = transformed_px(map_prop, width, height, win_prop)
				//+ offset_z((*win_prop)->divider / (*win_prop)->scale, next_map_height, map_prop)
				;
			/*if (pixel && next_pixel && pixel_in_screen(pixel, win_prop, map_prop) && pixel_in_screen(next_pixel, win_prop, map_prop))
				draw_line(map_prop, win_prop, pixel, next_pixel, map_height, next_map_height);*/
		}
		if (next_line && next_line[(*map_prop)->width] != NULL)
		{
			(*map_prop)->height++;
			next_line_next_map_height = ft_atoi_hex(next_line[(*map_prop)->width]);
			next_line_next_pixel = transformed_px(map_prop, width, height, win_prop)
				//+ offset_z((*win_prop)->divider / (*win_prop)->scale, next_line_next_map_height, map_prop)
				;
			//if (pixel && next_line_next_pixel && pixel_in_screen(pixel, win_prop, map_prop) && pixel_in_screen(next_line_next_pixel, win_prop, map_prop))
				//draw_line(map_prop, win_prop, next_line_pixel, next_line_next_pixel, map_height, next_line_next_map_height);
			(*map_prop)->height--;
		}

			if (pixel && next_pixel && next_line_pixel && next_line_next_pixel
			&& pixel_in_screen(pixel, win_prop, map_prop)
			&& pixel_in_screen(next_pixel, win_prop, map_prop)
			&& pixel_in_screen(next_line_pixel, win_prop, map_prop)
			&& pixel_in_screen(next_line_next_pixel, win_prop, map_prop)
			&& (*map_prop)->width >= (*win_prop)->cut_front
			&& (*map_prop)->width <= width - (*win_prop)->cut_back
			)
			{

				if ((*map_prop)->height < height-1)
				{
					if ((*win_prop)->v_down == 1)
						iterate_quad(map_prop, win_prop, pixel, next_pixel, next_line_pixel, next_line_next_pixel,
							map_height, next_map_height, next_line_map_height, next_line_next_map_height);
					draw_line(map_prop, win_prop, pixel, next_line_pixel, map_height, next_line_map_height);
				}
				draw_line(map_prop, win_prop, pixel, next_pixel, map_height, next_map_height);

			}
	}
	return (0);
}

static void	set_scale(t_win_prop **win_prop, t_map_prop **map_prop)
{
	if ((*win_prop)->scale == 0)
	{
		if ((*win_prop)->width / (*map_prop)->width
			< (*win_prop)->height / (*map_prop)->height)
			(*win_prop)->scale = (*win_prop)->width / ((*map_prop)->width);
		else
			(*win_prop)->scale = (*win_prop)->height / ((*map_prop)->height);
	}
	if ((*win_prop)->scale == 0)
		(*win_prop)->scale = 1;
}

int	draw(t_vars **vars, char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;
	char	**next_line = NULL;
	int		height;

	set_scale(win_prop, map_prop);
	height = (*map_prop)->height;
	(*map_prop)->height = 0;
	while (file_split[(*map_prop)->height] != NULL)
	{
		line = ft_split(file_split[(*map_prop)->height], ' ');
		if (file_split[(*map_prop)->height + 1] != NULL)
		{
			next_line = ft_split(file_split[(*map_prop)->height + 1], ' ');
			if (!next_line)
				return (-1);
		}
		if (!line)
			return (-1);
		line_print(line, next_line, map_prop, win_prop, height);
		free_mlx(line, NULL, NULL);
		//if (next_line && file_split[(*map_prop)->height + 1] != NULL)
			//free_mlx(next_line, NULL, NULL);
		(*map_prop)->height++;
	}
	strings(vars);
	return (0);
}
