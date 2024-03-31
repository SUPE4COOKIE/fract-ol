/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:46:52 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 04:58:43 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

size_t	julia(t_complex z, double c_re, double c_im)
{
	t_complex	complex_tmp;
	size_t		i;

	i = 0;
	while (i < MAX_ITER && !has_reached_limit(z))
	{
		complex_tmp = square_complex(z);
		z.re = complex_tmp.re + c_re;
		z.im = complex_tmp.im + 0.5251993;
		i++;
	}
	return (i);
}

size_t	mandelbrot(t_complex c)
{
	t_complex	z;
	t_complex	complex_tmp;
	size_t		i;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < MAX_ITER && !has_reached_limit(z))
	{
		complex_tmp = square_complex(z);
		z.re = complex_tmp.re;
		z.im = complex_tmp.im;
		z.re += c.re;
		z.im += c.im;
		i++;
	}
	return (i);
}
