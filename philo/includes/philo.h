/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:38:33 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 10:10:47 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORK 0
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
	int				time_to_think;
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
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*meal_lock;
	t_data			*data;
}	t_philo;

typedef struct s_args
{
	t_data	*data;
	t_philo	**philos;
}	t_args;

// Init

pthread_mutex_t	*init_mutex(void);
t_data			*init_data(void);
t_philo			**create_philosophers(t_data *data);

// Cleanup

void			destroy_mutex(pthread_mutex_t **mutex);
void			clear_data(t_data **data);
void			clear_philos(t_philo **philos, int size);
void			full_cleanup(t_data	**data, t_philo **philos);

// Parsing

void			usage(void);
t_data			*parsing(char **argv);

// Utils

long			print_action(int philo, t_data *data, int action);
int				has_someone_died(t_data *data);
long			time_since(struct timeval time);
int				msleep(int time, t_data *data, long start);
void			order_exit(t_data *data, int error);
int				has_eaten_enough(t_philo *philo, t_data *data);

// Actions

void			put_forks_down(t_philo	*philo);
int				take_forks(t_philo *philo, t_data *data);
int				think(int nphilo, t_data *data);
int				philosleep(int nphilo, t_data *data);
int				eat(t_philo *philo, t_data *data);

// Routines

void			*philosopher_life(void *arg);
void			monitor(t_args *args);

// Threads

int				create_threads(t_args *args);
void			wait_threads(t_philo **philos, t_data *data);

#endif
