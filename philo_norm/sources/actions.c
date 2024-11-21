/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:28:14 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/21 00:51:17 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	//printf("Vou tentar apanha os garfos %d\n", philo->name);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	if (philo->data->died != 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->write);
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d is eating\n", current_time_ml(philo), philo->name);
	pthread_mutex_unlock(&philo->data->write);
	if (philo->last_meal == 0)
		philo->last_meal = get_current_time();
	philo->eat_times++;
	if (ft_usleep(philo, philo->data->time_eat) == -1 && philo->data->died == 0)
	{
		printf("Vai largar os garfos erro%d\n", philo->name);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	//printf("Vai largar os garfos %d\n", philo->name);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->data->philos_finished != philo->data->philos_num && philo->last_meal != 0 && philo->data->died == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d is sleeping\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->data->time_think != 0 && philo->data->died == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d is thinking\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_think);
	}
}
