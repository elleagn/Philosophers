/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:39 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 08:51:11 by gozon            ###   ########.fr       */
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
