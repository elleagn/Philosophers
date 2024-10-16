/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:07:55 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 12:23:55 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	usage(void)
{
	printf("Usage:\n"
		"./philo number_of_philosophers time_to_die time_to_eat time_to_sleep"
		" [number_of_meals]\n");
}

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

int	convert_args(t_data *data, char **argv)
{
	data->nphilo = a_to_pos(argv[1]);
	if (data->nphilo <= 0)
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
		data->number_of_meals = a_to_pos(argv[5]);
		if (data->number_of_meals < 0)
			return (usage(), -1);
	}
	return (0);
}

t_data	*parsing(char **argv)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	if (convert_args(data, argv))
		return (clear_data(&data), NULL);
	if (data->nphilo % 2 && data->time_to_eat >= data->time_to_sleep)
		data->time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	return (data);
}
