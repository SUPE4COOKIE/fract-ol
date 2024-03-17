/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:52:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/17 19:45:33 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../includes/main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

unsigned	int	get_color(float i)
{
	unsigned int color;

	color = 0;
	color += (unsigned int)(9 * (1 - i) * pow(i, 3) * 255) << 16;
	color += (unsigned int)(15 * pow((1 - i), 2) * pow(i, 2) * 255) << 8;
	color += (unsigned int)(8.5 * pow((1 - i), 3) * i * 255);
	return (color);
}

t_complex pix_to_complex(size_t x, size_t y, t_mlx_data data)
{
	t_complex c;

	c.re = (x - (WIDTH / 2.0)) * (4.0 / WIDTH) / data.zoom + data.center.re;
	c.im = (y - (HEIGHT / 2.0)) * (4.0 / HEIGHT) / data.zoom + data.center.im;
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
	// magnitude of complex number
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
	while (i < 30 && !has_reached_limit(z))
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

void	render(t_mlx_data data)
{
	size_t x, y;

	y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				// map pixel to complex plane (???)
				t_complex c = pix_to_complex(x, y, data);
				c.re += data.x_offset;
				c.im += data.y_offset;
				size_t i = mandelbrot(c);
				size_t offset = (y * data.line_length) + (x * (data.bits_per_pixel / 8));
				unsigned int color = get_color((float)i / 30);
				*(unsigned int *)(data.pixels + offset) = color;
	
				x++;
			}
			y++;
		}
}

int	key_hook(int keycode, t_mlx_data *data)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 65361)
		data->x_offset -= data->move_value;
	if (keycode == 65363)
		data->x_offset += data->move_value;
	if (keycode == 65362)
		data->y_offset -= data->move_value;
	if (keycode == 65364)
		data->y_offset += data->move_value;
	if (keycode == 65451)
	{
		data->zoom *= 1.1;
		data->move_value /= 1.1;
	}
	if (keycode == 65453)
	{
		data->zoom /= 1.1;
		data->move_value *= 1.1;
	}
	render(*data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	close_hook(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	call_hooks(t_mlx_data *data)
{
	data->x_offset = 0;
	data->y_offset = 0;
	data->zoom = 1;
	data->center.re = 0;
	data->center.im = 0;
	data->move_value = 0.1;
	mlx_hook(data->win, 17, 0, close_hook, data);
	mlx_key_hook(data->win, key_hook, data);
}

int main(void)
{
    t_mlx_data data;
    size_t x, y;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.pixels = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	call_hooks(&data);
	render(data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}