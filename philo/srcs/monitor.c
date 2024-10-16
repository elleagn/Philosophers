/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:51:28 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 12:20:43 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	is_dead(t_philo *philo, t_data *data)
{
	long	time;

	if (pthread_mutex_lock(philo->meal_lock))
		return (order_exit(data, 1), -1);
	time = time_since(philo->start_of_latest_meal);
	pthread_mutex_unlock(philo->meal_lock);
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

int	monitor_death(t_args *args)
{
	int		i;
	int		someone_died;

	i = 0;
	someone_died = 0;
	while (i < args->data->nphilo)
	{
		if (is_dead(args->philos[i], args->data) == 1)
		{
			someone_died = 1;
			announce_death(i + 1, args->data);
			break ;
		}
		i++;
	}
	return (someone_died);
}

int	monitor_meal_number(t_args *args)
{
	int	philos_done;
	int	i;

	i = 0;
	philos_done = 0;
	while (i < args->data->nphilo)
	{
		if (has_eaten_enough(args->philos[i], args->data) != 1)
			break ;
		i++;
		philos_done += 1;
	}
	if (philos_done == args->data->nphilo)
		return (order_exit(args->data, 0), 1);
	return (0);
}

void	monitor(t_args *args)
{
	while (1 && !has_someone_died(args->data))
	{
		if (monitor_death(args))
			break ;
		if (args->data->number_of_meals >= 0 && monitor_meal_number(args))
			break ;
		if (usleep(1000))
			order_exit(args->data, 3);
	}
}
