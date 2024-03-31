/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:38 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 20:26:49 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define WIDTH 800
# define HEIGHT 800
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

typedef struct s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pixels;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	ftype;
	double	julia_re;
	double	julia_im;
	double	x_offset;
	double	y_offset;
	double	zoom;
	double	move_value;
}				t_mlx_data;

int				exit_mlx(t_mlx_data *data);
double			ft_atof(const char *nptr);
int				ft_isdigit(int c);
int				ft_isspace(char c);
int				check_coma(const char *nptr);
void			render(t_mlx_data data);
void			args_check(int ac, char **av, t_mlx_data *data);
void			set_julia(char **av, t_mlx_data *data);
int				frac_type(char *str, t_mlx_data *data);
void			render(t_mlx_data data);
int				key_hook(int keycode, t_mlx_data *data);
int				mouse_hook(int keycode, int x, int y, t_mlx_data *data);
void			call_hooks(t_mlx_data *data);
size_t			julia(t_complex z, double c_re, double c_im);
size_t			mandelbrot(t_complex c);
t_complex		pix_to_complex(size_t x, size_t y, t_mlx_data data);
t_complex		square_complex(t_complex z);
char			has_reached_limit(t_complex z);
unsigned int	get_color(float i);
# define MAX_ITER 100
#endif