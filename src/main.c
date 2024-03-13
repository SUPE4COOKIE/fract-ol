/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:52:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/13 11:31:03 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../includes/main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

unsigned int calculate_color(size_t iterations, size_t max_iterations) {
    if (iterations == max_iterations) {
        return 0x00000000; // Black for points inside the Mandelbrot set
    }

    // Calculate a gradient value between 0 and 255
    double t = (double)iterations / (double)max_iterations;
    unsigned char red = (unsigned char)(9 * (1 - t) * t * t * t * 255);
    unsigned char green = (unsigned char)(15 * (1 - t) * (1 - t) * t * t * 255);
    unsigned char blue =  (unsigned char)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return (red << 16) | (green << 8) | blue; // Combining the colors into a single integer
}

t_complex pix_to_complex(size_t x, size_t y)
{
	t_complex c;

	double minRe = -2.0;
    double maxRe = 1.0;
    double minIm = -1.2;
    double maxIm = minIm + (maxRe - minRe) * HEIGHT / WIDTH;

    c.re = minRe + (x / (double)WIDTH) * (maxRe - minRe);
    c.im = maxIm - (y / (double)HEIGHT) * (maxIm - minIm);

    return c;
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

int main(void)
{
    t_mlx_data data;
    size_t x, y;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.pixels = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

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

			unsigned int color = calculate_color(i, 100);
			*(unsigned int *)(data.pixels + offset) = color;

			x++;
		}
		y++;
	}

    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}