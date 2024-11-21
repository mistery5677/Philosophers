/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:42:22 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/20 19:36:04 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_full(t_data *data)
{
	unsigned int i;

	i = 0;
	while(i < data->philos_num)
	{
		if (data->philos[i].eat_times == data->meals_number)
			data->philos_finished++;
		if (data->philos_finished == data->philos_num)
		{
			//printf("brekou5\n");
			data->sim = 1;
			return 1;
		}
		if (data->died != 0)
		{
			//printf("brekou6\n");
			data->sim = 1;
			return 1;
		}
		i++;
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
		//usleep(1000);
	}
	return (NULL);
}