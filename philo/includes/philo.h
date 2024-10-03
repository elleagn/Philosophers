/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:38:33 by gozon             #+#    #+#             */
/*   Updated: 2024/10/03 11:17:14 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	start_time;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_lock;
	int				has_died;
}	t_data;

typedef struct s_philosopher
{
	int				num;
	pthread_t		thread_id;
	int				start_of_latest_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mealtime_lock;
	t_data			*data;
}	t_philosopher;

// Init functions

pthread_mutex_t	*init_mutex(void);
t_data			*init_data(void);

// Cleanup functions

void			destroy_mutex(pthread_mutex_t **mutex);
void			clear_data(t_data **data);

#endif
