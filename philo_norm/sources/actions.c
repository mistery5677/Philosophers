/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:28:14 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/22 11:34:26 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	//printf("Vou tentar apanha os garfos %d\n", philo->name);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->sync);
	if (philo->data->died != 0 || philo->eat_times == philo->data->meals_number)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->data->sync);
		return ;
	}
	pthread_mutex_unlock(&philo->data->sync);
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->sync);
	if (philo->data->died == 0 && philo->eat_times != philo->data->meals_number)
	{
		printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
		printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
		printf("%d %d is eating\n", current_time_ml(philo), philo->name);
	}
	pthread_mutex_unlock(&philo->data->sync);
	pthread_mutex_unlock(&philo->data->write);
	if (philo->last_meal == 0)
		philo->last_meal = get_current_time();
	philo->eat_times++;
	pthread_mutex_lock(&philo->data->sync);
	if (philo->eat_times == philo->data->meals_number)
		philo->data->philos_finished++;
	pthread_mutex_unlock(&philo->data->sync);
	if (ft_usleep(philo, philo->data->time_eat) == -1)
	{
		//printf("Vai largar os garfos erro%d\n", philo->name);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->data->sync);
	if (philo->last_meal == 0 && current_time_ml(philo) >= philo->data->time_die)
	{
		philo->data->died = philo->name;
		pthread_mutex_unlock(&philo->data->sync);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	else if (philo->last_meal != 0 && (get_current_time() - philo->last_meal) > philo->data->time_die)
	{
		philo->data->died = philo->name;
		pthread_mutex_unlock(&philo->data->sync);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->data->sync);
	//printf("Vai largar os garfos %d\n", philo->name);
	philo->last_meal = get_current_time();
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
	else 
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
