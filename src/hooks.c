/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:58:19 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/01 18:57:50 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
	render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_mlx_data *data)
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
	render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
