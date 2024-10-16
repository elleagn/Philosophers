/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:47:05 by gozon             #+#    #+#             */
/*   Updated: 2024/10/16 12:48:56 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 5 && argc != 6)
		return (usage(), 1);
	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	args->data = parsing(argv);
	if (!args->data)
		return (free(args), 1);
	args->philos = create_philosophers(args->data);
	if (create_threads(args))
		return (full_cleanup(&args->data, args->philos), free(args), 1);
	monitor((void *)args);
	wait_threads(args->philos, args->data);
	full_cleanup(&args->data, args->philos);
	free(args);
	return (0);
}
