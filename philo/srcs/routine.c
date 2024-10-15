/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:21:40 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 10:14:27 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->num % 2 == 0)
	{
		if (msleep(1, data, 0))
			return (NULL);
	}
	while (1)
	{
		if (eat(philo, data))
			break ;
		if (philosleep(philo->num, data))
			break ;
		if (think(philo->num, data))
			break ;
	}
	return (NULL);
}
