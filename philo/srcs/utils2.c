/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:57:38 by gozon             #+#    #+#             */
/*   Updated: 2024/10/15 08:48:14 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	order_exit(t_data *data, int error)
{
	pthread_mutex_lock(data->death_lock);
	data->has_died = 1;
	pthread_mutex_unlock(data->death_lock);
	if (error == 1)
		write(2, "Error locking mutex.\n", 22);
	if (error == 2)
		write(2, "Error getting time of day.\n", 28);
	if (error == 3)
		write(2, "Error sleeping\n", 16);
}
