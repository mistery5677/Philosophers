/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:27:49 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/30 19:34:14 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	obliterate_table(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
	{
		//if (&data->forks[i] != NULL)
			pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->sync);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == -1)
		return (-1);
	if (seat_the_philos(&data, argv) == -1)
	{
		printf("Something went wrong\n");
		return (-1);
	}
	obliterate_table(&data);
	return (0);
}
