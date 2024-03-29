/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:38 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/29 02:21:12 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIDTH 800
# define HEIGHT 800
# include <unistd.h>
typedef	struct s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct	s_mlx_data {
	void	*mlx;
	void 	*win;
	void	*img;
	char	*pixels;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	ftype;
	double	julie_re;
	double	julie_im;
	double	x_offset;
	double	y_offset;
	double	zoom;
	double	move_value;
}				t_mlx_data;
int	exit_mlx(t_mlx_data *data);
int	ft_atoi(const char *nptr);
# define MAX_ITER 100
#endif