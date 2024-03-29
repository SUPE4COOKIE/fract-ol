/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:01:24 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/29 17:04:18 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <float.h>

static	int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '.' || c == ',')
		return (1);
	return (0);
}
static int	ft_isspace(char c)
{
	if ((c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r'))
		return (1);
	return (0);
}

int	check_coma(const char *nptr)
{
	char	been_coma;
	size_t	coma_precision;
	size_t	i;

	been_coma = 0;
	coma_precision = 0;
	i = 0;
	while (nptr[i] && ft_isdigit((char)nptr[i]))
	{
		if ((nptr[i] == '.' || nptr[i] == ',') && !been_coma)
		{
			been_coma = 1;
			i++;
			continue;
		}
		else if ((nptr[i] == '.' || nptr[i] == ',') && been_coma)
			return (0);
		if (been_coma == 1)
			coma_precision++;
		i++;
	}
	if (coma_precision > 6)
		return (0);
	return (1);
}

float	ft_atof(const char *nptr)
{
	double	result;
	char	been_coma;
	double 	divider;
	int		sign;

	result = 0;
	divider = 1;
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
			result += (double)(*nptr - '0') / divider;
			divider *= 10;
		}
		else
			result = result * 10 + *nptr - '0';
		nptr++;
	}
	return ((float)(result * sign));
}
