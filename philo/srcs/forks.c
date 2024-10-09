/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:45:53 by gozon             #+#    #+#             */
/*   Updated: 2024/10/09 09:16:22 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	choose_fork_order(pthread_mutex_t **fork1, pthread_mutex_t **fork2,
t_philo *philo)
{
	if (philo->num / 2)
	{
		*fork1 = philo->right_fork;
		*fork2 = philo->left_fork;
	}
	else
	{
		*fork1 = philo->left_fork;
		*fork2 = philo->right_fork;
	}
}

int	take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				tstamp;

	choose_fork_order(&fork1, &fork2, philo);
	if (pthread_mutex_lock(fork1))
		return (printf("Error locking mutex\n"), -1);
	tstamp = time_since(data->start_time);
	if (tstamp < 0 || has_someone_died(data)
		|| print_action(philo->num, data, TAKE_FORK, tstamp))
		return (pthread_mutex_unlock(fork1), -1);
	if (pthread_mutex_lock(fork2))
		return (printf("Error locking mutex\n"),
			pthread_mutex_unlock(fork1), -1);
	tstamp = time_since(data->start_time);
	if (tstamp < 0 || has_someone_died(data)
		|| print_action(philo->num, data, TAKE_FORK, tstamp))
		return (pthread_mutex_unlock(fork1), pthread_mutex_unlock(fork2), -1);
	return (0);
}

void	put_forks_down(t_philo	*philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
