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
# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct vec
{
	int	x;
	int	y;
}	t_vec2;

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
void			set_moon_color(unsigned char *pixel, int map_height, t_win_prop **win_prop);
int				draw(t_vars **vars, char **file_split, t_map_prop **map_prop,
					t_win_prop **win_prop);
int				offset_z(int multiplier, int map_height, t_map_prop **map_prop);
int				centering_offset_y(t_win_prop **win_prop, int height);
int				centering_offset_x(t_win_prop **win_prop, int width);
int				perspective_offset_x(t_win_prop **win_prop, int out_x,
					int out_y, int height);
int				perspective_offset_y(t_map_prop **map_prop, int height);
t_vec2			map_to_sphere(t_vec2 p, t_vec2 w_h, int radiusX, int radiusY);
unsigned char	*transformed_px(t_map_prop **map_prop, int width,
					int height, t_win_prop **win_prop);
int				draw_object(t_object *object, t_win_prop **win_prop);
unsigned char	*transformed_px_object(t_object *object, int width,
					int height, t_win_prop **win_prop);
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

#endif
