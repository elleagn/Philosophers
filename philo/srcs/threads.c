/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 08:57:15 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 12:58:54 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex)
		return (write(2, "Error allocating memory.\n", 26), NULL);
	if (pthread_mutex_init(mutex, NULL))
		return (free(mutex), write(2, "Error initializing mutex.\n", 27), NULL);
	return (mutex);
}

void	destroy_mutex(pthread_mutex_t **mutex)
{
	if (pthread_mutex_destroy(*mutex))
		write(2, "Error destroying mutex.\n", 25);
	free(*mutex);
	*mutex = NULL;
}

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
