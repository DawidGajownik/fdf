/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ftoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:17:48 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/10 16:17:49 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ftoa(char *first, char *second, char *third, char *fourth)
{
	free(first);
	free(second);
	free(third);
	free(fourth);
}
