/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:52:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/16 18:44:17 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../includes/main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_complex pix_to_complex(size_t x, size_t y)
{
	t_complex c;

	c.re = (x - (WIDTH / 2.0)) * 4.0 / WIDTH;
	c.im = (y - (HEIGHT / 2.0)) * 4.0 / HEIGHT;
	return (c);
}

t_complex square_complex(t_complex z)
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

size_t mandelbrot(t_complex c)
{
	t_complex	z;
	t_complex	complex_tmp;
	size_t		i;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < 100 && !has_reached_limit(z))
	{
		//square complex
		complex_tmp = square_complex(z);
		z.re = complex_tmp.re;
		z.im = complex_tmp.im;
		// add c
		z.re += c.re;
		z.im += c.im;
		i++;
	}
	return (i);
}

void	render(int i, t_mlx_data data)
{
	size_t x, y;

	y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				// map pixel to complex plane (???)
				t_complex c = pix_to_complex(x, y);
				size_t i = mandelbrot(c);
				size_t offset = (y * data.line_length) + (x * (data.bits_per_pixel / 8));
				unsigned int color = gradientColor((float)i / 100);
				*(unsigned int *)(data.pixels + offset) = color;
	
				x++;
			}
			y++;
		}
}

int main(void)
{
    t_mlx_data data;
    size_t x, y;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.pixels = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	render(-1, data);

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}