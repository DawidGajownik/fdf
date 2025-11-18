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
#include <stdio.h>

static unsigned int rgb(unsigned char r, unsigned char g, unsigned char b)
{
    return (r << 16) | (g << 8) | b;
}

static unsigned int lerp_color(unsigned int c1, unsigned int c2, float t)
{
    unsigned char r1 = (c1 >> 16) & 0xFF;
    unsigned char g1 = (c1 >> 8)  & 0xFF;
    unsigned char b1 =  c1        & 0xFF;

    unsigned char r2 = (c2 >> 16) & 0xFF;
    unsigned char g2 = (c2 >> 8)  & 0xFF;
    unsigned char b2 =  c2        & 0xFF;

    unsigned char r = r1 + (r2 - r1) * t;
    unsigned char g = g1 + (g2 - g1) * t;
    unsigned char b = b1 + (b2 - b1) * t;

    return rgb(r, g, b);
}

unsigned int get_height_color(int h)
{
    const unsigned int DEEP_BLUE = 0x00000080;
    const unsigned int BLUE      = 0x000080FF;
    const unsigned int GREEN     = 0x0000FF00;
    const unsigned int BROWN     = 0x007A4A00;
    const unsigned int WHITE     = 0x00FFFFFF;

    if (h <= 0)
        return DEEP_BLUE;

    if (h <= 200) {
        float t = (float)h / 200.0f;
        return lerp_color(BLUE, GREEN, t);
    }

    if (h <= 1000) {
        float t = (float)(h - 200) / 800.0f;
        return lerp_color(GREEN, BROWN, t);
    }

    if (h <= 3000) {
        float t = (float)(h - 1000) / 2000.0f;
        return lerp_color(BROWN, WHITE, t);
    }

    return WHITE;
}

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

unsigned int color_from_height(int map_height)
{
    const int minH = 1200;
    const int maxH = 3100;

    // Kolory początkowe i końcowe
    const unsigned int r1 = 0xF5, g1 = 0x6A, b1 = 0x15; // 0x00F56A15
    const unsigned int r2 = 0xFF, g2 = 0xFF, b2 = 0xFF; // 0x00FFFFFF

    // Ograniczenie zakresu
    if (map_height < minH) map_height = minH;
    if (map_height > maxH) map_height = maxH;

    // Współczynnik 0.0 – 1.0
    float t = (float)(map_height - minH) / (float)(maxH - minH);

    // Interpolacja każdego kanału
    unsigned int r = r1 + (unsigned int)((r2 - r1) * t);
    unsigned int g = g1 + (unsigned int)((g2 - g1) * t);
    unsigned int b = b1 + (unsigned int)((b2 - b1) * t);

    // Format 0x00RRGGBB
    return (0x00 << 24) | (r << 16) | (g << 8) | b;
}


void	set_color(unsigned char *pixel, int map_height, t_map_prop **map_prop, t_win_prop **win_prop)
{
	if (pixel_in_range_if_zero_grades(pixel, map_prop, win_prop)
	 //&& (!pixel_out(pixel, map_prop) || (*map_prop)->width == 0)
	 )
	{
	//ft_printf("%d", map_height);
		if (map_height <= 0)
		{
		*(unsigned int *)pixel = 0x00AAAAFF
		//chuj wie
			+ 256 * 256
			* (map_height/32
			)
			* (256 / (*map_prop)->low_high_diff)
		//odejmuje zolty
			 + 256
			* (map_height/32
			)
			* (256 / (*map_prop)->low_high_diff)
		
		//odejmuje czerwony
		/* + 
		(map_height
		 - (*map_prop)->height_offset
		)
		* (256 / (*map_prop)->low_high_diff)*/
			;
		}
		else if (map_height < 300)
		{
			*(unsigned int *)pixel = 0x00AAFFAA
		//chuj wie
			- 256 * 256
			* (map_height/2
		// - (*map_prop)->height_offset
			)
			//* (256 / (*map_prop)->low_high_diff)
		//odejmuje zolty
			 - 256
			* (map_height/2
		// - (*map_prop)->height_offset
			)
			//* (256 / (*map_prop)->low_high_diff)
		/*==*/
		//odejmuje czerwony
			 - 
			(map_height/2
		// - (*map_prop)->height_offset
			)
			//* (256 / (*map_prop)->low_high_diff)
			;
		}
		else if (map_height < 1200)
		{
			
			*(unsigned int *)pixel = 
			0x00156A15
			+
			(map_height-300)/4*
			(256*256
			//-0x00006A00
			);
			if (map_height == 1199)
				ft_printf("%X\n", *(unsigned int *)pixel); 
			
		}
		else
		{
			*(unsigned int *)pixel = color_from_height(map_height);
			/*0x00F56A15
			+
			//1876			655360
			(map_height - 1200)*((10*256*256)/256/256/100)*256*256
			+
			(map_height - 1200)*((149*256)/256/200)*256
			+
			(map_height - 1200)*234/200
			//(map_height-1200)/10*/
			//*(256)
			//;
		}
		/*else
		{
			*(unsigned int *)pixel = 
			0x00152915
			+
			(map_height-850)/50*
			(
			(36*256*256
			+149*256
			+234
			)/256/256)
			
			;
		}*/
			//*(unsigned int *)pixel = 0x00FFFFFF;
	}
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
		set_color(pixel, map_height, map_prop, win_prop);
	}
	scale = (*win_prop)->scale;
	pixel = temp_pixel;
	while (scale-- > 0)
	{
		pixel = pixel + (*map_prop)->line_size;
		pix_hor_corr(&pixel, map_prop, scale);
		set_color(pixel, map_height, map_prop, win_prop);
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

int	offset_z(int multiplier, int map_height, t_map_prop **map_prop)
{
	return -(map_height/multiplier*(*map_prop)->bytes_pp
			+ (map_height/multiplier)*(*map_prop)->line_size*(*map_prop)->bytes_pp);
}

unsigned char	*rotated_px(unsigned char *pixel, t_map_prop **map_prop, int width, int height, t_win_prop **win_prop

//int x, int y, int angle_deg
//, int *out_x, int *out_y
)
{
	//ft_printf("%d %d\n", pixel, img_data);
	int diff = (pixel - (*map_prop)->img_data)/(*map_prop)->bytes_pp;
	int divider = (*map_prop)->line_size/(*map_prop)->bytes_pp*(*win_prop)->scale;
	int y = height*(*win_prop)->scale/2-diff/divider*(*win_prop)->scale;
	int x = -((*map_prop)->line_size/(*map_prop)->bytes_pp/2-(diff - (height*(*win_prop)->scale/2-y)/(*win_prop)->scale*divider));
	//ft_printf("diff = %d height = %d width = %d linesize = %d scale = %d divider - %d y = %d x = %d\n", diff, height, width,
		//(*map_prop)->line_size, (*win_prop)->scale, divider, y, x);
	double angle_rad = (*map_prop)->grades * M_PI / 200.0;
	
	
	double cosA = cos(angle_rad);
	double sinA = sin(angle_rad);

    // obliczenia w double → zaokrąglenie do int
	double nx = x * cosA - y * sinA;
	double ny = x * sinA + y * cosA;

	int out_x = (int)round(nx);
	int out_y = (int)round(ny);
	
    // print w środku funkcji
	//printf("Stare koordynaty: (%d, %d)\n", x, y);
	//printf("Kat obrotu: %d stopni\n", (*map_prop)->grades);
	//printf("Nowe koordynaty: (%d, %d)\n\n", out_x, out_y);
	int diff_y = (height * (*win_prop)->scale / 2 - out_y);
	diff_y = (diff_y * divider) / (*win_prop)->scale;

// ODWROTNOŚĆ X: z (out_x) → diff_x
	int diff_x = out_x + divider/2;

// SUMA → finalny diff
	int out_diff = diff_y + diff_x;

// ODWROTNOŚĆ diff → pointer
	unsigned char *out_pixel =
    	(*map_prop)->img_data + out_diff * (*map_prop)->bytes_pp;
    	return (out_pixel);
	//ft_printf("new_pointer = %d\n", (out_pixel-(*map_prop)->img_data)/(*map_prop)->bytes_pp);
}

int	line_print(char **line, t_map_prop **map_prop, t_win_prop **win_prop, int height)
{
	unsigned char	*pixel;
	int i;
	int j;
	int width;
	int offset_x;
	int offset_y;
	int offset_xx;
	int offset_yy;
	int offset;
	int offsret;
	int map_height;
	int scale;
	
	j = 0;
	width = (*map_prop)->width;
	(*map_prop)->width = 0;
	
	while (line[(*map_prop)->width])
	{
		
		map_height = ft_atoi(line[(*map_prop)->width]);
		pixel = (*map_prop)->img_data
			+ (*map_prop)->width * (*map_prop)->bytes_pp * (*win_prop)->scale
			+ (*map_prop)->height * (*map_prop)->line_size * (*win_prop)->scale
			//+ offset_x_based_on_sinus(width, height, map_prop, win_prop)
			//+ offset_x_works_but_makes_it_bigger(height, map_prop, win_prop)
			//+ offset_y_works_but_makes_it_bigger(height, map_prop, win_prop)
			//+ offset_z(1500, map_height, map_prop)
			//+ offset_y_only_for_ninety_degrees(height, map_prop, win_prop)
			//+ offset_x_only_for_ninety_degrees(height, map_prop, win_prop)
			;
		pixel = rotated_px(pixel, map_prop, width, height, win_prop);
		//if (pixel_out(pixel, map_prop))
			//break;
		//*(unsigned int *)pixel = get_height_color(map_height);
		set_color(pixel, map_height, map_prop, win_prop);
		draw_lines(map_height, pixel, map_prop, win_prop);
		(*map_prop)->width++;
	}
	return (0);
}

int	draw(char **file_split, t_map_prop **map_prop, t_win_prop **win_prop)
{
	char	**line;
	int	height;

	if ((*win_prop)->width/(*map_prop)->width < (*win_prop)->height/(*map_prop)->height)
		(*win_prop)->scale = (*win_prop)->width/(*map_prop)->width;
	else
		(*win_prop)->scale = (*win_prop)->height/(*map_prop)->height;
	(*win_prop)->scale = (*win_prop)->scale*2;
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
	char		**file_split;

	if (init_all(&win_prop, &vars, &map_prop, filename) < 0)
		return (-1);
	file_split = ft_split(vars->file_content, '\n');
	win_prop->file_split = ft_split(vars->file_content, '\n');
	if (set_res(file_split, &map_prop) < 0)
		return (-1);
	draw(file_split, &map_prop, &win_prop);
	//set_padding(&win_prop, &map_prop);
	///if (img_gen(file_split, &map_prop, &win_prop) < 0)
		//return (-1);
	free_mlx(file_split, &win_prop, &map_prop);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mouse_actions(vars->win, win_prop);

	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	double i = -1.0;

	while (i < 400.0)
	{
   		double rad = i * M_PI / 180.0;

    		/*printf("%f°: sin = %f, cos = %f, tg = %f, ctg = %f\n",
        	i,
        	sin(rad),
        	cos(rad),
        	tan(rad),
        	cos(rad) / sin(rad)
    	);*/
    	i = i + 1.0;
}
	fdf(argv[1]);
	return (0);
}
