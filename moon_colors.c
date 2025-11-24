/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moon_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:12:38 by dgajowni          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:40 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	set_moon_color(unsigned char *pixel, int map_height)
{
	int	shade;

	if (map_height < -8000)
		map_height = -8000;
	if (map_height > 8000)
		map_height = 8000;
	shade = (map_height + 8000) * 255 / 16000;
	*(unsigned int *)pixel = (0xFF << 24)
		| (shade << 16)
		| (shade << 8)
		| (shade);
}
