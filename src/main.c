/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:52:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 04:56:16 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	exit_mlx(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	place_pixel(t_mlx_data *data, size_t x, size_t y, size_t i)
{
	size_t			offset;
	unsigned int	color;

	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	color = get_color((float)i);
	*(unsigned int *)(data->pixels + offset) = color;
}

void	render(t_mlx_data data)
{
	size_t		x;
	size_t		y;
	size_t		i;
	t_complex	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = pix_to_complex(x, y, data);
			c.re += data.x_offset;
			c.im += data.y_offset;
			if (data.ftype == 'm')
				i = mandelbrot(c);
			else if (data.ftype == 'j')
				i = julia(c, data.julie_re, data.julie_im);
			place_pixel(&data, x, y, i);
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	args_check(ac, av, &data);
	if (data.ftype == 'j' && ac == 4)
		set_julia(av, &data);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		write(2, "error while initiating the mlx\n", 31);
		exit(0);
	}
	if (data.ftype == 'm')
		data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
	else
		data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Julia");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.pixels = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
					&data.line_length, &data.endian);
	call_hooks(&data);
	render(data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
