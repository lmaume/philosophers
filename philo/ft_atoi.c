/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:52 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/20 11:51:28 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
}

int	ft_atoi(char *nptr, int *error)
{
	int		i;
	int		sign;
	long	reslut;

	i = 0;
	sign = 1;
	reslut = 0;
	if (ft_strncmp(nptr, "-2147483648", ft_strlen("-2147483648")) == 0)
		return (-2147483648);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32 \
	|| nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		reslut = (reslut * 10) + (nptr[i] - '0');
		if (reslut < -2147483648 || reslut > 2147483647)
			*error = 1;
		i++;
	}
	return (sign * reslut);
}
