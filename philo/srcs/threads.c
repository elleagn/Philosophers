/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:57:15 by gozon             #+#    #+#             */
/*   Updated: 2024/10/10 09:52:42 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	create_threads(t_data *data)
{
	int		i;
	t_philo	**philos;

	i = 0;
	if (pthread_create(&data->monitor_id, NULL, monitor, (void *)data))
		return (1);
	while (i < data->nphilo)
	{
		if (pthread_create(&philos[i]->thread_id, NULL, philosopher_life,
				(void *)philos[i]))
		{
			pthread_mutex_lock(data->death_lock);
			data->has_died = 1;
			pthread_mutex_unlock(data->death_lock);
			wait_threads(i, philos, data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	wait_threads(int n, t_philo **philos, t_data *data)
{
	int		i;
	void	*val_ptr;

	i = 0;
	pthread_join(data->monitor_id, &val_ptr);
	while (i < n)
	{
		pthread_join(philos[i]->thread_id, &val_ptr);
		i++;
	}
}
