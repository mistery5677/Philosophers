/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:42:22 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/24 21:25:18 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_full(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (data->philos_finished == data->philos_num)
		{
			data->sim = 1;
			return (1);
		}
		if (data->died != 0)
		{
			data->sim = 1;
			return (1);
		}
		pthread_mutex_lock(&data->sync);
		i++;
		pthread_mutex_unlock(&data->sync);
	}
	return (0);
}

void	*conditions(void *table)
{
	t_data	*data;

	data = (t_data *)table;
	data->died = 0;
	while (1)
	{
		if (data->died != 0)
		{
			data->sim = 1;
			break ;
		}
		if (check_full(data) == 1)
		{
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
