/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:57:43 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 19:57:43 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_object(t_vars **vars, t_object **object, char *filename)
{
	*object = malloc(sizeof(t_object));
	if (!*object)
		return (-1);
	(*object)->file_content = read_file(filename, &(*object)->bytes_read);
	if (!(*object)->file_content)
		return (-1);
	(*object)->file_content[(*object)->bytes_read] = '\0';
	(*object)->file_split = ft_split((*object)->file_content, '\n');
	(*object)->scale = 0;
	(*object)->img = mlx_new_image((*vars)->mlx,
			(*vars)->win_prop->width / 4, (*vars)->win_prop->height / 4);
	if (!(*object)->img)
		return (-1);
	(*object)->img_data = mlx_get_data_addr((*object)->img, &(*object)->bits_pp,
			&(*object)->line_size, &(*object)->endian);
	if (!(*object)->img_data)
		return (-1);
	(*object)->bytes_pp = (*object)->bits_pp / 8;
	(*object)->width = 0;
	(*object)->height = 0;
	(*object)->offset_x = 0;
	(*object)->offset_y = 0;
	(*object)->last_x = 0;
	(*object)->last_y = 0;
	(*vars)->object = *object;
}
