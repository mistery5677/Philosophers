/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:42:22 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/31 16:51:08 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->sync);
	if (data->died != 0)
	{
		pthread_mutex_unlock(&data->sync);
		return 1;
	}
	pthread_mutex_unlock(&data->sync);
	return 0;
}

static int	check_full(t_data *data)
{
	unsigned int i;

	i = 0;
	while(i < data->philos_num)
	{
		pthread_mutex_lock(&data->sync);
		if (data->philos[i].eat_times == data->meals_number)
			data->philos_finished++;
		pthread_mutex_unlock(&data->sync);
		i++;
	}
	if (data->philos_finished == data->philos_num)
	{
		data->sim = 1;
		return 1;
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
		if (check_full(data) == 1 || check_dead(data) == 1)
			break;
		return NULL;
	}
	return (NULL);
}