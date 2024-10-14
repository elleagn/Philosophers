/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:51:46 by gozon             #+#    #+#             */
/*   Updated: 2024/10/14 11:44:41 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (gettimeofday(&data->start_time, NULL))
		return (NULL);
	data->print_lock = init_mutex();
	if (!data->print_lock)
		return (free(data), NULL);
	data->death_lock = init_mutex();
	if (!data->death_lock)
		return (destroy_mutex(&data->print_lock), free(data), NULL);
	data->nphilo = -1;
	data->time_to_die = -1;
	data->time_to_eat = -1;
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
