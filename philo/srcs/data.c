/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:51:46 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 09:04:21 by gozon            ###   ########.fr       */
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
