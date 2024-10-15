/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:57:15 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 08:52:18 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	create_threads(t_args *args)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = args->philos;
	while (i < args->data->nphilo)
	{
		if (pthread_create(&philos[i]->thread_id, NULL, philosopher_life,
				(void *)philos[i]))
		{
			pthread_mutex_lock(args->data->death_lock);
			args->data->has_died = 1;
			pthread_mutex_unlock(args->data->death_lock);
			write(2, "Error creating thread.\n", 24);
			wait_threads(philos, args->data);
			return (1);
		}
		i++;
	}
	return (0);
}

void	wait_threads(t_philo **philos, t_data *data)
{
	int		i;
	void	*val_ptr;

	i = 0;
	while (i < data->nphilo && philos[i]->thread_id)
	{
		pthread_join(philos[i]->thread_id, &val_ptr);
		i++;
	}
}
