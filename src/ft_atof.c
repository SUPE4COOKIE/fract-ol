/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:01:24 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 04:07:33 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


static double	return_overflow(long double result)
{
	if (result > DBL_MAX)
	{
		write(2, "Overflow\n", 9);
		exit(1);
	}
	if (result < -DBL_MAX)
	{
		write(2, "Underflow\n", 10);
		exit(1);
	}
	return ((double)result);
}

static double dbl_conversion(const char *nptr, int sign)
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
			continue;
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
	return (return_overflow(result * sign));
}

double	ft_atof(const char *nptr)
{
	long double	result;
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
