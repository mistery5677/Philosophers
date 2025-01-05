/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:35 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/05 01:40:04 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sync);
	if (philo->data->died != 0 || philo->data->philos_finished
		== philo->data->philos_num)
	{
		pthread_mutex_unlock(&philo->data->sync);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->sync);
	return (0);
}

static int	do_routine(t_philo *philo)
{
	if (check_sim(philo) == 1)
		return (1);
	eat(philo);
	if (check_sim(philo) == 1)
		return (1);
	ft_sleep(philo);
	if (check_sim(philo) == 1)
		return (1);
	thinking(philo);
	return (0);
}

void	*routine(void *data)
{
	unsigned int	died;
	t_philo			*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		ft_usleep(philo, philo->data->time_eat);
	while (do_routine(philo) == 0)
		;
	pthread_mutex_lock(&philo->data->sync);
	died = philo->data->died;
	pthread_mutex_unlock(&philo->data->sync);
	if (died == philo->name)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d died\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (NULL);
}
