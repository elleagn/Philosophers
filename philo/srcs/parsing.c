/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:07:55 by gozon             #+#    #+#             */
/*   Updated: 2024/10/02 16:49:20 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	a_to_pos(const char *nptr)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (-1);
		nbr = 10 * nbr + (nptr[i] - '0');
		if (nbr > 2147483647)
			return (-1);
		i++;
	}
	return ((int) nbr);
}

int	parse_args(t_data *data, char **argv)
{
	data->number_of_philosophers = a_to_pos(argv[1]);
	if (data->number_of_philosophers <= 0)
		return (usage(), -1);
	data->time_to_die = a_to_pos(argv[2]);
	if (data->time_to_die < 0)
		return (usage(), -1);
	data->time_to_eat = a_to_pos(argv[3]);
	if (data->time_to_eat < 0)
		return (usage(), -1);
	data->time_to_sleep = a_to_pos(argv[4]);
	if (data->time_to_sleep < 0)
		return (usage(), -1);
	if (argv[5])
	{
		data->number_of_meals = a_to_ms(argv[2]);
		if (data->number_of_meals < 0)
			return (usage(), -1);
	}
	return (0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: init_data"), data);
	data->death_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->death_lock)
		return (printf("Error: init_data"), free(data), NULL);
	data->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->print_lock)
		return (printf("Error: init_data"), free(data->death_lock),
			free(data), NULL);
	data->has_died = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->start_time.tv_sec = 0;
	data->start_time.tv_usec = 0;
}

t_data	*prepare_data(char **argv)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	if (parse_args(data, argv))
		return (clear_data(data), NULL);
}
