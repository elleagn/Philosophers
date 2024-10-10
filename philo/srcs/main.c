/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:47:05 by gozon             #+#    #+#             */
/*   Updated: 2024/10/10 10:00:43 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// ACTUAL MAIN
int	main(int argc, char **argv)
{
	t_data	*data;
	void	*value;

	if (argc != 5 && argc != 6)
		return (usage(), 1);
	data = parsing(argv);
	if (!data)
		return (1);
	data->philos = create_philosophers(data);
	if (gettimeofday(&data->start_time, NULL))
		return (full_cleanup(&data, data->philos), 1);
	if (create_threads(data))
		return (full_cleanup(&data, data->philos), 1);
	wait_threads(data->nphilo, data->philos, data);
	full_cleanup(&data, data->philos);
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
