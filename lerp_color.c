/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:08:01 by dgajowni          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:02 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_ch(int c, int shift)
{
	return ((c >> shift) & 0xFF);
}

static int	lerp_val(int a, int b, float t)
{
	return ((int)((1.0f - t) * a + t * b));
}

int	lerp_color(int c1, int c2, float t)
{
	int	r[2];
	int	g[2];
	int	b[2];
	int	out[3];
	int	i;

	r[0] = get_ch(c1, 16);
	g[0] = get_ch(c1, 8);
	b[0] = get_ch(c1, 0);
	r[1] = get_ch(c2, 16);
	g[1] = get_ch(c2, 8);
	b[1] = get_ch(c2, 0);
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			out[i] = lerp_val(r[0], r[1], t);
		else if (i == 1)
			out[i] = lerp_val(g[0], g[1], t);
		else
			out[i] = lerp_val(b[0], b[1], t);
		i++;
	}
	return ((out[0] << 16) | (out[1] << 8) | out[2]);
}
