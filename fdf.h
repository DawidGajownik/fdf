/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:41:03 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/11 15:41:04 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50000000
# endif

# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct vec
{
	int	x;
	int	y;
}	t_vec2;

typedef struct color
{
	int	r[5];
	int	g[5];
	int	b[5];
}	t_color;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_object
{
	ssize_t			bytes_read;
	char			*file_content;
	char			**file_split;
	void			*img;
	unsigned char	*img_data;
	unsigned int	width;
	unsigned int	height;
	unsigned int	bits_pp;
	unsigned int	bytes_pp;
	unsigned int	line_size;
	unsigned int	endian;
	unsigned int	scale;
	unsigned int	grades;
	int				last_x;
	int				last_y;
	int				offset_x;
	int				offset_y;
}	t_object;

typedef struct s_map_prop
{
	int				height;
	int				width;
	unsigned int	grades;
	unsigned int	prev_grades;
	unsigned int	rotation;
	unsigned int	bits_pp;
	unsigned int	bytes_pp;
	unsigned char	*img_data;
	unsigned int	line_size;
	unsigned int	endian;
	ssize_t			bytes_read;
	int				height_offset;
	int				low_high_diff;
}	t_map_prop;

typedef struct s_win_prop
{
	unsigned int	width;
	unsigned int	height;
	double			scale;
	double			prev_scale;
	unsigned int	padding;
	int				mouse_down;
	int				ctrl_down;
	int				q_down;
	int				c_down;
	int				a_down;
	int				w_down;
	int				s_down;
	int				x_down;
	int				b_down;
	int				v_down;
	int				z_down;
	int				last_x;
	int				last_y;
	int				offset_x;
	int				offset_y;
	int				sphere_correction_x;
	int				sphere_correction_y;
	char			**file_split;
	int				divider;
	int				prev_divider;
	float			color_scaler;
	float			prev_color_scaler;
	int				cut_front;
	int				cut_back;
}	t_win_prop;

typedef struct s_bres
{
	t_vec2	p;
	t_vec2	n;
	t_vec2	p0;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	float	full;
}	t_bres;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*file_content;
	t_win_prop	*win_prop;
	t_map_prop	*map_prop;
	t_size		size;
	t_object	*object;
}	t_vars;

char			**ft_split(char const *s, char c);
int				ft_printf(const char *format, ...);
int				ft_atoi(const char *nptr);
int				close_window(void *param);
void			free_mlx(char **split, t_win_prop **win_prop,
					t_map_prop **map_prop);
char			*read_file(char *filename, ssize_t *bytes_read);
int				init_all(t_win_prop **win_prop, t_vars **vars,
					t_map_prop **map_prop, char *filename);
int				set_res(char **file_split, t_map_prop **map_prop);
void			set_padding(t_win_prop **win_prop, t_map_prop **map_prop);
int				img_gen(char **file_split, t_map_prop **map_prop,
					t_win_prop **win_prop);
int				fdf(char *filename, char *filename2);
void			set_hipsometric_color(unsigned char *pixel, int map_height,
					t_map_prop **map_prop, t_win_prop **win_prop);
int				init_object(t_vars **vars, t_object **object, char *filename);
int				set_res_object(t_object *object);
void			set_hipsometric_color_object(unsigned char *pixel,
					int map_height, t_object *object, t_win_prop **win_prop);
void			set_moon_color(unsigned char *pixel, int map_height,
					t_win_prop **win_prop, int lvl);
int				draw(t_vars **vars, char **file_split, t_map_prop **map_prop,
					t_win_prop **win_prop);
int				offset_z(t_win_prop **win_prop, int map_height,
					t_map_prop **map_prop);
int				centering_offset_y(t_win_prop **win_prop, int height);
int				centering_offset_x(t_win_prop **win_prop, int width);
int				perspective_offset_x(t_win_prop **win_prop, int out_x,
					int out_y, int height);
int				perspective_offset_y(t_map_prop **map_prop, int height);
t_vec2			map_to_sphere(t_vec2 p, t_vec2 w_h, int radiusX, int radiusY);
unsigned char	*transformed_px(t_vars **vars, t_size s, int map_height);
int				draw_object(t_object *object, t_win_prop **win_prop);
unsigned char	*transformed_px_object(t_object *object, t_size s,
					t_win_prop **win_prop);
int				globe_move(void *param);
int				actions(t_vars **vars);
int				mouse_move(int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_press(int button, int x, int y, void *param);
int				key_press(int keycode, void *param);
void			keys_map(int keycode, t_vars **vars);
int				key_release(int keycode, void *param);
int				key_hook(int keycode, void *param);
void			redraw(t_vars **vars);
void			redraw_object(t_vars **vars);
unsigned int	color_1200_plus(int map_height);
unsigned int	color_300_1200(int map_height);
unsigned int	color_0_300(int map_height);
unsigned int	color_0_minus_object(int map_height, t_object *object);
unsigned int	color_0_minus(int map_height, t_map_prop **map_prop);
int				init_object(t_vars **vars, t_object **object, char *filename);
void			strings(t_vars **vars);
char			*ft_ftoa(float f, int precision);
char			*ft_strjoin(const char *s1, const char *s2, int q);
unsigned int	ft_atoi_hex(const char *str);
void			set_color_blue(unsigned char *pixel, int map_height,
					t_win_prop **win_prop, int lvl);
void			set_color_green(unsigned char *pixel, int map_height,
					t_win_prop **win_prop, int lvl);
void			set_color_red(unsigned char *pixel, int map_height,
					t_win_prop **win_prop, int lvl);
unsigned int	brighten_color(unsigned int color, int amount);
t_bres			bres_setup(t_vec2 p, t_vec2 n);
int				bres_height(t_bres *b, t_win_prop **win,
					int h1, int h2);
void			bres_pixel(unsigned char *px, int mh,
					t_map_prop **mp, t_win_prop **win);
void			bres_step(t_bres *b);
int				pixel_in_bounds(t_vec2 p, t_win_prop **win);
unsigned char	*get_pixel_addr(t_vec2 p,
					t_map_prop **mp, t_win_prop **win);
float			distance(t_vec2 a, t_vec2 b);
int				lerp_color(int c1, int c2, float t);
int				line_print(char **line[2], t_vars **vars, t_size s);
void			iterate_quad(t_map_prop **map_prop, t_win_prop **win_prop,
					unsigned char *px[4], int mh[4]);
unsigned char	*set_lower_point_data(int *map_height, t_vars **vars,
					char **line, t_size s);
unsigned char	*set_point_data(int *map_height, t_vars **vars,
					char **line, t_size s);
int				set_map_height(t_vars **vars, char **line);
int				weighted_color(t_vec2 p[5], int c[4]);
int				weighted_height(t_vec2 p[5], int mh[4]);
void			bresenham(t_vec2 p[2], t_map_prop **mp,
					t_win_prop **win, int h[2]);
void			get_all_coords(unsigned char *px[4], t_map_prop **map_prop,
					t_win_prop **win_prop, t_vec2 p[5]);
void			strings_one(t_vars **vars, void *mlx, void *win, int c[2]);
void			strings_two(t_vars **vars, void *mlx, void *win, int c[2]);
void			strings_three(t_vars **vars, void *mlx, void *win, int c[2]);
void			strings_four(t_vars **vars, void *mlx, void *win, int c[2]);
void			strings_five(t_vars **vars, void *mlx, void *win, int c[2]);
void			free_ftoa(char *first, char *second, char *third, char *fourth);
void			print_last_line(unsigned char *pixel[4], int map_height[4],
					t_vars **vars, t_size s);
int				draw_line(t_map_prop **map_prop, t_win_prop **win_prop,
					char *pixel[2], int map_height[2]);
char			pixel_in_screen(unsigned char *pixel,
					t_win_prop **win_prop, t_map_prop **map_prop);
int				free_after_error(t_vars **vars, t_win_prop **win_prop,
					t_map_prop **map_prop);

#endif
