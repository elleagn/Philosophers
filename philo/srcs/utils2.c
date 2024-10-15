/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:57:38 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 09:19:10 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	order_exit(t_data *data, int error)
{
	pthread_mutex_lock(data->death_lock);
	data->has_died = 1;
	pthread_mutex_unlock(data->death_lock);
	if (error == 1)
		write(2, "Error locking mutex.\n", 22);
	if (error == 2)
		write(2, "Error getting time of day.\n", 28);
	if (error == 3)
		write(2, "Error sleeping\n", 16);
}

int	has_eaten_enough(t_philo *philo, t_data *data)
{
	int	meals;

	if (pthread_mutex_lock(philo->meal_lock))
		return (order_exit(data, 1), -1);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(philo->meal_lock);
	if (meals >= data->number_of_meals)
		return (1);
	return (0);
}
