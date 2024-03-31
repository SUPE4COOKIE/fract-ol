/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:56:23 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 20:02:46 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_complex	pix_to_complex(size_t x, size_t y, t_mlx_data data)
{
	t_complex	c;

	c.re = (x - (WIDTH / 2.0)) * (4.0 / WIDTH) / data.zoom;
	c.im = (y - (HEIGHT / 2.0)) * (4.0 / HEIGHT) / data.zoom;
	return (c);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.re = (z.re * z.re) - (z.im * z.im);
	result.im = 2 * (z.re * z.im);
	return (result);
}

char	has_reached_limit(t_complex z)
{
	if (sqrt((z.re * z.re) + (z.im * z.im)) > 2)
		return (1);
	return (0);
}

unsigned int	get_color(float i)
{
	unsigned int	color;

	color = 0;
	if (i == MAX_ITER)
		return (0x000000);
	i = sin(sqrt(i));
	color += (unsigned int)((i) * 255) << 16;
	color += (unsigned int)((i) * 255) << 8;
	color += (unsigned int)((i) * 255) *255;
	return (color);
}
