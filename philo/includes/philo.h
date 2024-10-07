/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:38:33 by gozon             #+#    #+#             */
/*   Updated: 2024/10/07 08:29:34 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_data
{
	int				nphilo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	start_time;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_lock;
	int				has_died;
}	t_data;

typedef struct s_philo
{
	int				num;
	pthread_t		thread_id;
	struct timeval	start_of_latest_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mealtime_lock;
	t_data			*data;
}	t_philo;

// Init

pthread_mutex_t	*init_mutex(void);
t_data			*init_data(void);
t_philo			**create_philosophers(t_data *data);

// Cleanup

void			destroy_mutex(pthread_mutex_t **mutex);
void			clear_data(t_data **data);
void			clear_philos(t_philo **philos, int size);

// Parsing

void			usage(void);
t_data			*parsing(char **argv);

#endif
