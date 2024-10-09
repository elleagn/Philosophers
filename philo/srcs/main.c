/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:47:05 by gozon             #+#    #+#             */
/*   Updated: 2024/10/08 11:44:48 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*take_and_put_forks_down(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!take_forks(philo, philo->data))
		put_forks_down(philo);
	return (NULL);
}

// ACTUAL MAIN
int	main(void)
{
	t_data	*data;
	t_philo	**philos;
	int		i;
	void	*value;

	i = 0;
	// if (argc != 5 && argc != 6)
	// 	return (usage(), 1);
	data = init_data();
	if (!data)
		return (1);
	data->nphilo = 2;
	philos = create_philosophers(data);
	if (gettimeofday(&data->start_time, NULL))
		return (full_cleanup(&data, philos), 1);
	while (i < data->nphilo)
	{
		if (pthread_create(&philos[i]->thread_id, NULL, take_and_put_forks_down,
				(void *)philos[i]))
			break ;
		i++;
	}
	while (i-- > 0)
		pthread_join(philos[i]->thread_id, &value);
	full_cleanup(&data, philos);
	return (0);
}

// void	*first_thread(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	i = 0;
// 	while (i++ < 2)
// 	{
// 		usleep(1);
// 		print_action(1, data, EAT, 0);
// 		print_action(1, data, SLEEP, 1);
// 		print_action(1, data, THINK, 2);
// 		print_action(1, data, DIE, 3);
// 	}
// 	return (NULL);
// }

// void	*second_thread(void *arg)
// {
// 	t_data	*data;

// 	data = (t_data *)arg;
// 	usleep(1);
// 	print_action(2, data, EAT, 0);
// 	print_action(2, data, SLEEP, 1);
// 	print_action(2, data, THINK, 2);
// 	print_action(2, data, DIE, 3);
// 	return (NULL);
// }

// int	main(void)
// {
// 	t_data		*data;
// 	pthread_t	*t1;
// 	pthread_t	*t2;
// 	void		*value;

// 	data = init_data();
// 	if (!data)
// 		return (1);
// 	t1 = malloc(sizeof(pthread_t));
// 	t2 = malloc(sizeof(pthread_t));
// 	if (!t1 || !t2)
// 		return (free(t1), free(t2), 1);
// 	if (pthread_create(t1, NULL, first_thread, (void *)data))
// 		return (1);
// 	if (pthread_create(t2, NULL, second_thread, (void *)data))
// 		return (pthread_join(*t1, &value), 1);
// 	pthread_join(*t1, &value);
// 	free(t1);
// 	pthread_join(*t2, &value);
// 	free(t2);
// 	clear_data(&data);
// 	return (0);
// }
