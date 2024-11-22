/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:39:08 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/22 11:50:52 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	get_think(t_data *data)
{
	if (data->philos_num % 2 == 0)
	{
		if (data->time_eat > data->time_sleep)
			data->time_think = data->time_eat - data->time_sleep;
		else
			data->time_think = 0;
	}
	else
	{
		if (data->time_eat * 2 > data->time_sleep)
			data->time_think = (data->time_eat * 2) - data->time_sleep;
		else
			data->time_think = 0;
	}
}

static int	initialize_status(t_data *data, char **argv)
{
	data->philos_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	get_think(data);
	printf("time think %d\n", data->time_think);
	if (argv[5])
		data->meals_number = ft_atoi(argv[5]);
	else
		data->meals_number = -1;
	data->philos = malloc((data->philos_num) * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->philos_finished = 0;
	data->start_time = get_current_time();
	data->died = 0;
	data->sim = 0;
	return (0);
}

static int	initialize_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->sync, NULL);
	data->forks = malloc(data->philos_num * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (-1);
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (-1);
		i++;
	}
	i = 0;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[data->philos_num - 1];
	while (++i < data->philos_num)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i - 1];
	}
	return (0);
}

static int	born_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philos_num)
	{
		data->philos[i].name = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_times = 0;
		data->philos[i].last_meal = 0;
		if (pthread_create(&data->philos[i].id, NULL, routine,
				&data->philos[i]) == -1)
			return (-1);
		i++;
	}
	pthread_create(&data->supervisor, NULL, conditions, data);
	i = 0;
	pthread_join(data->supervisor, NULL);
	while (i < data->philos_num)
	{
		if (pthread_join(data->philos[i].id, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	seat_the_philos(t_data *data, char **argv)
{
	if (initialize_status(data, argv) == -1)
		return (-1);
	if (initialize_mutex(data) == -1)
		return (-1);
	if (check_status(data) == -1)
		return (-2);
	if (born_philos(data) == -1)
		return (-1);
	return (0);
}
