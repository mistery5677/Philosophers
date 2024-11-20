/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:09:50 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/20 01:19:43 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned int	current_time_ml(t_philo *philo)
{
	return (get_current_time() - philo->data->start_time);
}

int	ft_usleep(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		//pthread_mutex_lock(&philo->data->mut_dead);
		if (philo->data->died == 0
			&& (get_current_time() - philo->last_meal) > philo->data->time_die)
		{
			philo->data->died = philo->name;
			return (-1);
		}
		//pthread_mutex_unlock(&philo->data->mut_dead);
		usleep(500);
	}
	return (0);
}
