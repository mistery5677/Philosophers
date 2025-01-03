/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:28:14 by mistery576        #+#    #+#             */
/*   Updated: 2024/12/31 16:57:55 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	unlock_forks(t_philo *philo, int flag)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (flag == 1)
		pthread_mutex_unlock(&philo->data->sync);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->write);
	if (check_sim(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->write);
		unlock_forks(philo, 0);
		return ;
	}
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d is eating\n", current_time_ml(philo), philo->name);
	pthread_mutex_unlock(&philo->data->write);
	philo->last_meal = get_current_time();
	philo->eat_times++;
	pthread_mutex_lock(&philo->data->sync);
	if (philo->eat_times == philo->data->meals_number)
		philo->data->philos_finished++;
	pthread_mutex_unlock(&philo->data->sync);
	ft_usleep(philo, philo->data->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->philos_finished != philo->data->philos_num && philo->last_meal != 0 && philo->data->died == 0 )
	{
		printf("%d %d is sleeping\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_sleep);
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->time_think != 0 && philo->data->died == 0 && philo->data->philos_finished != philo->data->philos_num)
	{
		printf("%d %d is thinking\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_think);
	}
	else
		pthread_mutex_unlock(&philo->data->write);
}
