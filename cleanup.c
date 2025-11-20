/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:00:03 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/13 16:00:05 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	free_mlx(vars->win_prop->file_split, &vars->win_prop, &vars->map_prop);
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->file_content)
		free(vars->file_content);
	free(vars);
	exit(0);
	return (0);
}

void	free_mlx(char **split, t_win_prop **win_prop, t_map_prop **map_prop)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i++]);
	}
	if (split)
		free(split);
	if (win_prop)
		free(*win_prop);
	if (map_prop)
		free(*map_prop);
}
