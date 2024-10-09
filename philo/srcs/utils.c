/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:42:55 by gozon             #+#    #+#             */
/*   Updated: 2024/10/09 10:04:19 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	has_someone_died(t_data *data)
{
	int	res;

	pthread_mutex_lock(data->death_lock);
	if (data->has_died)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(data->death_lock);
	return (res);
}

int	print_action(int philo_nb, t_data *data, int action, int timestamp)
{
	pthread_mutex_t	*print_lock;

	(void)data;
	print_lock = data->print_lock;
	if (action != DIE && has_someone_died(data))
		return (1);
	pthread_mutex_lock(print_lock);
	if (action == TAKE_FORK)
		printf("%i %i has taken a fork\n", timestamp, philo_nb);
	else if (action == EAT)
		printf("%i %i is eating\n", timestamp, philo_nb);
	else if (action == SLEEP)
		printf("%i %i is sleeping\n", timestamp, philo_nb);
	if (action == THINK)
		printf("%i %i is thinking\n", timestamp, philo_nb);
	if (action == DIE)
		printf("%i %i died\n", timestamp, philo_nb);
	pthread_mutex_unlock(print_lock);
	if (has_someone_died(data))
		return (1);
	return (0);
}

long	time_since(struct timeval time)
{
	long			interval;
	struct timeval	now;

	if (gettimeofday(&now, NULL))
		return (printf("Error getting current time\n"), -1);
	interval = 1000 * (long)(now.tv_sec - time.tv_sec)
		+ (long)(now.tv_usec - time.tv_usec) / 1000;
	return (interval);
}

void	full_cleanup(t_data	**data, t_philo **philos)
{
	clear_philos(philos, (*data)->nphilo);
	clear_data(data);
}

int	msleep(int time, t_data *data)
{
	int	i;

	i = 0;
	while (i < time)
	{
		if (usleep(1000))
			return (1);
		if (has_someone_died(data))
			return (1);
		i++;
	}
	return (0);
}
