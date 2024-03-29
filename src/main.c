/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:52:59 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/29 03:00:37 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../includes/main.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/keysym.h>

unsigned	int	get_color(float i)
{
	unsigned int color;

	color = 0;
	if (i == MAX_ITER)
		return (0x000000);
	i = sqrt(i / MAX_ITER);
	color += (unsigned int)((i) * 255) << 16;
	color += (unsigned int)((i) * 255) << 8;
	color += (unsigned int)((i) * 255) * 255;
	return (color);
}

t_complex pix_to_complex(size_t x, size_t y, t_mlx_data data)
{
	t_complex c;

	c.re = (x - (WIDTH / 2.0)) * (4.0 / WIDTH) / data.zoom;
	c.im = (y - (HEIGHT / 2.0)) * (4.0 / HEIGHT) / data.zoom;
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

size_t julia(t_complex z, double c_re, double c_im)
{
    t_complex complex_tmp;
    size_t i = 0;

    while (i < MAX_ITER && !has_reached_limit(z))
    {
        // square complex
        complex_tmp = square_complex(z);
        z.re = complex_tmp.re + c_re;
        z.im = complex_tmp.im + 0.5251993;
        i++;
    }
    return i;
}

size_t mandelbrot(t_complex c)
{
	t_complex	z;
	t_complex	complex_tmp;
	size_t		i;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < MAX_ITER && !has_reached_limit(z))
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
	size_t x;
	size_t y;
	size_t i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			t_complex c = pix_to_complex(x, y, data);
			c.re += data.x_offset;
			c.im += data.y_offset;
			if (data.ftype == 'm')
				i = mandelbrot(c);
			else if (data.ftype == 'j')
				i = julia(c, data.julie_re, data.julie_im);
			size_t offset = (y * data.line_length) + (x * (data.bits_per_pixel / 8));
			unsigned int color = get_color((float)i);
			*(unsigned int *)(data.pixels + offset) = color;

			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_mlx_data *data)
{
	if (keycode == XK_Left)
		data->x_offset -= data->move_value;
	if (keycode == XK_Right)
		data->x_offset += data->move_value;
	if (keycode == XK_Up)
		data->y_offset -= data->move_value;
	if (keycode == XK_Down)
		data->y_offset += data->move_value;
	if (keycode == XK_Escape)
		exit_mlx(data);
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

int mouse_hook(int keycode,int x, int y, t_mlx_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 4)
	{
		data->zoom *= 1.1;
		data->move_value /= 1.1;
	}
	if (keycode == 5)
	{
		data->zoom /= 1.1;
		data->move_value *= 1.1;
	}
	render(*data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	exit_mlx(t_mlx_data *data)
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
	data->move_value = 0.1;
	mlx_hook(data->win, 17, 0, exit_mlx, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
}

int	frac_type(char *str, t_mlx_data *data)
{
	if ((str[0] == 'j' || str[0] == 'J') && str[1] == '\0')
	{
		data->ftype = 'j';
		data->julie_re = -0.5251993;
		data->julie_im = 0.5251993;
		return (1);
	}
	if ((str[0] == 'm' || str[0] == 'M') && str[1] == '\0')
	{
		data->ftype = 'm';
		return (1);
	}
	return (0);
}

void	args_check(int ac, char **av, t_mlx_data *data)
{
	if (ac < 2)
	{
		write(2, "Usage: ./fractol [j/m]\n", 23);
		exit(0);
	}
	if (ac > 2 && ac < 4)
	{
		write(2, "Usage: ./fractol j <julia_real> <julia_imaginary>\n", 49);
		exit(0);
	}
	if (!frac_type(av[1], data))
	{
		write(2, "Usage: ./fractol [j/m]\n", 23);
		exit(0);
	}
	if (ac > 2 && data->ftype == 'm')
	{
		write(2, "Usage: ./fractol m\n", 20);
		exit(0);
	}
	if (ac > 4)
	{
		write(2, "Usage: ./fractol [j/m]\n", 23);
		exit(0);
	}
}

void	set_julia(char **av, t_mlx_data *data)
{
	// atof implementation
	data->julie_re = ft_atoi(av[2]);
	data->julie_im = ft_atoi(av[3]);
}

int main(int ac, char **av)
{
    t_mlx_data data;

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
    data.pixels = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	call_hooks(&data);
	render(data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return (0);
}