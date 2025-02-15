/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:51:46 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 12:53:23 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error allocating memory.\n", 26), NULL);
	if (gettimeofday(&data->start_time, NULL))
		return (write(2, "Error getting time of day.\n", 28), NULL);
	data->print_lock = init_mutex();
	if (!data->print_lock)
		return (free(data), NULL);
	data->death_lock = init_mutex();
	if (!data->death_lock)
		return (destroy_mutex(&data->print_lock), free(data), NULL);
	data->nphilo = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
	data->time_to_think = 0;
	data->time_to_sleep = -1;
	data->number_of_meals = -1;
	data->has_died = 0;
	return (data);
}

void	clear_data(t_data **data)
{
	destroy_mutex(&(*data)->print_lock);
	destroy_mutex(&(*data)->death_lock);
	free(*data);
	*data = NULL;
}

t_philo	*init_philo(t_data *data, int nb)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num = nb;
	philo->thread_id = 0;
	philo->start_of_latest_meal = data->start_time;
	philo->meals_eaten = 0;
	philo->left_fork = NULL;
	philo->right_fork = init_mutex();
	if (!philo->right_fork)
		return (free(philo), NULL);
	philo->meal_lock = init_mutex();
	if (!philo->meal_lock)
		return (destroy_mutex(&philo->meal_lock), free(philo), NULL);
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
		destroy_mutex(&philos[i]->meal_lock);
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
