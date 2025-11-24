/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:59:39 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 15:59:41 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_file(char *filename, ssize_t *bytes_read)
{
	int		fd;
	char	*file_content;

	fd = open(filename, O_RDONLY);
	if (!fd < 0)
		return (NULL);
	file_content = malloc(BUFFER_SIZE + 1);
	if (!file_content)
		return (NULL);
	*bytes_read = read(fd, file_content, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	close(fd);
	file_content[*bytes_read] = '\0';
	return (file_content);
}

static int	vars_init(t_vars **vars, t_win_prop **win_prop, char *filename)
{
	(*vars)->mlx = mlx_init();
	if (!(*vars)->mlx)
		return (-1);
	(*vars)->win = mlx_new_window((*vars)->mlx, (*win_prop)->width + 400,
			(*win_prop)->height, filename);
	if (!(*vars)->win)
		return (-1);
	(*vars)->img = mlx_new_image((*vars)->mlx,
			(*win_prop)->width, (*win_prop)->height);
	if (!(*vars)->img)
		return (-1);
	(*vars)->win_prop = *win_prop;
	return (0);
}

static int	map_init(t_vars **vars, t_map_prop **map_prop)
{
	(*map_prop)->width = 0;
	(*map_prop)->height = 0;
	(*map_prop)->height_offset = 0;
	(*map_prop)->low_high_diff = 0;
	(*map_prop)->grades = 0;
	(*map_prop)->img_data = mlx_get_data_addr((*vars)->img,
			&(*map_prop)->bits_pp, &(*map_prop)->line_size,
			&(*map_prop)->endian);
	if (!(*map_prop)->img_data)
		return (-1);
	(*map_prop)->bytes_pp = (*map_prop)->bits_pp / 8;
	(*vars)->map_prop = *map_prop;
	return (0);
}

static void	win_init(t_win_prop **win_prop, char **file_content)
{
	(*win_prop)->file_split = ft_split(file_content, '\n');
	(*win_prop)->width = 1080;
	(*win_prop)->height = 1080;
	(*win_prop)->padding = 0;
	(*win_prop)->offset_x = 0;
	(*win_prop)->offset_y = 0;
	(*win_prop)->scale = 0;
	(*win_prop)->mouse_down = 0;
	(*win_prop)->ctrl_down = 0;
	(*win_prop)->q_down = 0;
	(*win_prop)->c_down = 0;
	(*win_prop)->a_down = 0;
	(*win_prop)->w_down = 0;
	(*win_prop)->s_down = 0;
	(*win_prop)->x_down = 0;
	(*win_prop)->last_x = 0;
	(*win_prop)->last_y = 0;
	(*win_prop)->offset_x = 0;
	(*win_prop)->offset_y = 0;
	(*win_prop)->sphere_correction_x = 0;
	(*win_prop)->sphere_correction_y = 0;
}

int	init_all(t_win_prop **win_prop, t_vars **vars,
t_map_prop **map_prop, char *filename)
{
	*vars = malloc(sizeof(t_vars));
	if (!*vars)
		return (-1);
	*map_prop = malloc(sizeof(t_map_prop));
	if (!*map_prop)
		return (-1);
	*win_prop = malloc(sizeof(t_win_prop));
	if (!*win_prop)
		return (-1);
	(*vars)->file_content = read_file(filename, &(*map_prop)->bytes_read);
	if (!(*vars)->file_content)
		return (-1);
	win_init(win_prop, (*vars)->file_content);
	if (vars_init(vars, win_prop, filename) < 0)
		return (-1);
	if (map_init(vars, map_prop) < 0)
		return (-1);
	return (0);
}
