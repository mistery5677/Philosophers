/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:27:49 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/10 15:34:53 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	obliterate_table(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->sync);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write (2, "Wrong number of arguments\n", 26);
		return (-1);
	}
	if (check_args(argv) == -1)
		return (-1);
	if (seat_the_philos(&data, argv) == -1)
	{
		if (data.meals_number == 0)
			printf("Philos don't want to eat\n");
		else
			printf("Something went wrong\n");
		return (-1);
	}
	obliterate_table(&data);
	return (0);
}
