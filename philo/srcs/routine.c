/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:21:40 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 08:13:12 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
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

int	is_dead(t_philo *philo, t_data *data)
{
	long	time;

	if (pthread_mutex_lock(philo->mealtime_lock))
		return (order_exit(data), -1);
	time = time_since(philo->start_of_latest_meal);
	pthread_mutex_unlock(philo->mealtime_lock);
	if (time < 0)
		return (-1);
	if (time > data->time_to_die)
		return (1);
	return (0);
}

void	announce_death(int nphilo, t_data *data)
{
	pthread_mutex_lock(data->death_lock);
	data->has_died = 1;
	pthread_mutex_unlock(data->death_lock);
	print_action(nphilo, data, DIE);
}

void	monitor(t_args *args)
{
	int		i;

	i = 0;
	while (1 && !has_someone_died(args->data))
	{
		i = (i + 1) % args->data->nphilo;
		if (is_dead(args->philos[i], args->data) == 1)
			announce_death(i + 1, args->data);
	}
}
