/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:07:55 by gozon             #+#    #+#             */
/*   Updated: 2024/09/27 13:58:43 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoms(const char *nptr)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (-1);
		nbr = 10 * nbr + (nptr[i] - '0');
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	return ((int) nbr);
}
