/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:01:24 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 20:48:58 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <stdio.h>

static double	dbl_conversion(const char *nptr, int sign)
{
	long double	result;
	size_t		divider;
	char		been_coma;

	divider = 1;
	result = 0;
	been_coma = 0;
	while (*nptr && ft_isdigit((unsigned char)*nptr))
	{
		if (*nptr == '.' || *nptr == ',')
		{
			been_coma = 1;
			nptr++;
			continue ;
		}
		if (been_coma)
		{
			divider *= 10;
			result += (long double)(*nptr - '0') / divider;
		}
		else
			result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (result * sign);
}

double	ft_atof(const char *nptr)
{
	int			sign;

	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	if (!check_coma(nptr))
	{
		write(2, "Invalid input\n", 14);
		exit(1);
	}
	return (dbl_conversion(nptr, sign));
}
