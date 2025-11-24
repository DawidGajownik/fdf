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

int	proceed_second_parameter(t_vars **vars, char *filename2)
{
	t_object	*moon;

	if (filename2 != NULL)
	{
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

	if (init_all(&win_prop, &vars, &map_prop, filename) < 0
		|| set_res(win_prop->file_split, &map_prop) < 0
		|| draw(win_prop->file_split, &map_prop, &win_prop) < 0)
		return (-1);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 400, 0);
	if (proceed_second_parameter(&vars, filename2) < 0)
		return (-1);
	actions(&vars);
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
