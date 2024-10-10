/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:11:56 by gozon             #+#    #+#             */
/*   Updated: 2024/10/10 13:56:12 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	update_mealtime(t_philo *philo, struct timeval start)
{
	long	tstamp;

	if (pthread_mutex_lock(philo->mealtime_lock))
		return (-1);
	if (gettimeofday(&philo->start_of_latest_meal, NULL))
		return (pthread_mutex_unlock(philo->mealtime_lock), -1);
	tstamp = (long)((philo->start_of_latest_meal.tv_sec - start.tv_sec) * 1000
			+ (philo->start_of_latest_meal.tv_usec - start.tv_usec) / 1000);
	pthread_mutex_unlock(philo->mealtime_lock);
	return (tstamp);
}

int	eat(t_philo *philo, t_data *data)
{
	int	tstamp;

	if (take_forks(philo, data))
		return (1);
	tstamp = update_mealtime(philo, data->start_time);
	if (tstamp < 0 || print_action(philo->num, data, EAT, tstamp)
		|| msleep(data->time_to_eat, data))
		return (put_forks_down(philo), 1);
	put_forks_down(philo);
	return (0);
}

int	philosleep(int nphilo, t_data *data)
{
	long	tstamp;

	tstamp = time_since(data->start_time);
	if (tstamp < 0 || print_action(nphilo, data, SLEEP, tstamp))
		return (1);
	if (msleep(data->time_to_sleep, data))
		return (1);
	return (0);
}

int	think(int nphilo, t_data *data)
{
	long	tstamp;

	tstamp = time_since(data->start_time);
	if (tstamp < 0 || print_action(nphilo, data, THINK, tstamp))
		return (1);
	return (0);
}
