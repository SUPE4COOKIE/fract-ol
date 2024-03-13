/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:38 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/13 10:41:58 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIDTH 800
# define HEIGHT 800

typedef struct	s_mlx_data {
	void	*mlx;
	void 	*win;
	void	*img;
	char	*pixels;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx_data;

typedef	struct s_complex
{
	double	re;
	double	im;
}				t_complex;

#endif