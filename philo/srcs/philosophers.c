/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 09:18:02 by gozon             #+#    #+#             */
/*   Updated: 2024/10/11 11:42:16 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo	*init_philo(t_data *data, int nb)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num = nb;
	philo->thread_id = 0;
	philo->start_of_latest_meal = data->start_time;
	philo->meals_left = data->number_of_meals;
	philo->left_fork = NULL;
	philo->right_fork = init_mutex();
	if (!philo->right_fork)
		return (free(philo), NULL);
	philo->mealtime_lock = init_mutex();
	if (!philo->mealtime_lock)
		return (destroy_mutex(&philo->mealtime_lock), free(philo), NULL);
	philo->data = data;
	return (philo);
}

void	clear_philos(t_philo **philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		destroy_mutex(&philos[i]->right_fork);
		destroy_mutex(&philos[i]->mealtime_lock);
		free(philos[i]);
		i++;
	}
	free(philos);
}

t_philo	**create_philosophers(t_data *data)
{
	t_philo	**philo_array;
	int		i;

	i = 0;
	philo_array = malloc(data->nphilo * sizeof(t_philo *));
	if (!philo_array)
		return (NULL);
	while (i < data->nphilo)
	{
		philo_array[i] = init_philo(data, i + 1);
		if (!philo_array[i])
			return (clear_philos(philo_array, i + 1), NULL);
		i++;
	}
	i = 0;
	while (data->nphilo > 1 && i < data->nphilo)
	{
		philo_array[i]->left_fork
			= philo_array[(i + 1) % data->nphilo]->right_fork;
		i++;
	}
	return (philo_array);
}
