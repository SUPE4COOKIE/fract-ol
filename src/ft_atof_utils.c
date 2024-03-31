/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:52:20 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/03/31 01:52:26 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '.' || c == ',')
		return (1);
	return (0);
}
int	ft_isspace(char c)
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
		coma_precision++;
		i++;
	}
	if (coma_precision > 15)
		return (0);
	return (1);
}