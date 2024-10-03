/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:39 by gozon             #+#    #+#             */
/*   Updated: 2024/10/02 17:12:37 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(mutex));
	if (!mutex)
		return (printf("Allocation failed"), NULL);
	if (pthread_mutex_init(mutex, NULL))
		return (free(mutex), printf("Mutex initialization failed\n"), NULL);
	return (NULL);
}

void	destroy_mutex(pthread_mutex_t **mutex)
{
	if (pthread_mutex_destroy(*mutex))
		printf("Destroy mutex failed\n");
	free(*mutex);
	*mutex = NULL;
}
