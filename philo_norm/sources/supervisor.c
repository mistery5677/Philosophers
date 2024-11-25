/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:42:22 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/22 00:18:36 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_full(t_data *data)
{
	unsigned int i;

	i = 0;
	while(i < data->philos_num)
	{	
		//printf("Philo %d  philos->finished %d\n", data->philos[i].name, data->philos_finished);
		if (data->philos_finished == data->philos_num)
		{
			// pthread_mutex_lock(&data->write);
			// printf("Vou mudar o valor da sim pq estao todos cheios\n");
			// pthread_mutex_unlock(&data->write);
			data->sim = 1;
			return 1;
		}
		if (data->died != 0)
		{
			// pthread_mutex_lock(&data->write);
			// printf("Alguem morreu\n");
			// pthread_mutex_unlock(&data->write);
			//printf("brekou6\n");
			data->sim = 1;
			return 1;
		}
		pthread_mutex_lock(&data->sync);
		i++;
		pthread_mutex_unlock(&data->sync);
		//printf("encrementou o i\n");
	}
	return 0;
}

void *conditions(void *table)
{
	t_data	*data;

	data = (t_data *)table;
	data->died = 0;
	while(1)
	{
		if (data->died != 0)
		{
			//printf("brekou2\n");
			data->sim = 1;
			break ;
		}
		if (check_full(data) == 1)
		{
			//printf("brekou3\n");
			break ;
		}
		usleep(500);
	}
	return (NULL);
}