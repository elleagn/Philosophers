/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:47:05 by gozon             #+#    #+#             */
/*   Updated: 2024/10/07 09:14:54 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	if (argc != 5 && argc != 6)
		return (usage(), 1);
	data = parsing(argv);
	if (!data)
		return (1);
	philos = create_philosophers(data);
	printf("%p, %p\n", philos[0]->left_fork, philos[1]->right_fork);
	clear_philos(philos, data->nphilo);
	return (0);
}
