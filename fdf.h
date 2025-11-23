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

typedef struct s_size
{
  int width;
  int height;
} t_size;

typedef struct s_object {
	ssize_t			bytes_read;
	char	*file_content;
	char	**file_split;
	void	*img;
	unsigned char	*img_data;
	unsigned int	width;
	unsigned int	height;
	unsigned int	bits_pp;
	unsigned int	bytes_pp;
	unsigned int	line_size;
	unsigned int	endian;
	unsigned int	scale;
	unsigned int	grades;
	int	last_x;
	int	last_y;
	int offset_x;
	int offset_y;
}	t_object;

typedef struct s_map_prop
{
	int	height;
	int	width;
	unsigned int	grades;
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
	unsigned int	scale;
	unsigned int	padding;
	int	mouse_down;
	int     ctrl_down;
	int     q_down;
	int		c_down;
	int		a_down;
	int		w_down;
	int		s_down;
	int		x_down;
	int	last_x;
	int	last_y;
	int offset_x;
	int offset_y;
	int sphere_correction_x;
	int sphere_correction_y;
	char **file_split;
}	t_win_prop;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*file_content;
	t_win_prop  *win_prop;
	t_map_prop  *map_prop;
	t_size size;
	t_object	*object;
}	t_vars;

char	**ft_split(char const *s, char c);
int		ft_printf(const char *format, ...);
int		ft_atoi(const char *nptr);
int		close_window(void *param);
void	free_mlx(char **split, t_win_prop **win_prop, t_map_prop **map_prop);
char	*read_file(char *filename, ssize_t *bytes_read);
int		init_all(t_win_prop **win_prop, t_vars **vars,
			t_map_prop **map_prop, char *filename);
int		set_res(char **file_split, t_map_prop **map_prop);
void	set_padding(t_win_prop **win_prop, t_map_prop **map_prop);
int		img_gen(char **file_split, t_map_prop **map_prop,
			t_win_prop **win_prop);
int		fdf(char *filename, char *filename2);
void	set_hipsometric_color(unsigned char *pixel, int map_height,
			t_map_prop **map_prop, t_win_prop **win_prop);
int	init_object(t_vars **vars, t_object **object, char *filename);
int	set_res_object(t_object *object);
void	set_hipsometric_color_object(unsigned char *pixel, int map_height, t_object *object, t_win_prop **win_prop);
void	set_moon_color(unsigned char *pixel, int map_height);



#endif
