/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:57:41 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 04:57:07 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
		write(2, "Usage: ./fractol j <julia_real> <julia_imaginary>\n", 50);
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
	data->julie_re = ft_atof(av[2]);
	data->julie_im = ft_atof(av[3]);
}
