/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:11:56 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 08:58:48 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	update_mealtime(t_philo *philo)
{
	if (pthread_mutex_lock(philo->meal_lock))
		return (order_exit(philo->data, 1), -1);
	if (gettimeofday(&philo->start_of_latest_meal, NULL))
		return (pthread_mutex_unlock(philo->meal_lock),
			order_exit(philo->data, 2), -1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	eat(t_philo *philo, t_data *data)
{
	int	tstamp;

	if (take_forks(philo, data))
		return (1);
	if (update_mealtime(philo))
		return (1);
	tstamp = print_action(philo->num, data, EAT);
	if (tstamp < 0)
		return (order_exit(data, 2), 1);
	if (msleep(data->time_to_eat, data, tstamp))
		return (put_forks_down(philo), 1);
	put_forks_down(philo);
	return (0);
}

int	philosleep(int nphilo, t_data *data)
{
	long	tstamp;

	tstamp = print_action(nphilo, data, SLEEP);
	if (tstamp < 0)
		return (order_exit(data, 2), 1);
	if (msleep(data->time_to_sleep, data, tstamp))
		return (1);
	return (0);
}

int	think(int nphilo, t_data *data)
{
	if (print_action(nphilo, data, THINK) < 0)
		return (1);
	return (0);
}
