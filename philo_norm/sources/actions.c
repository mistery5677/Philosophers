/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:28:14 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/04 23:05:03 by mistery576       ###   ########.fr       */
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
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
		
			
	// Garante a ordem consistente
	if (philo->r_fork < philo->l_fork)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}

	// Bloqueia os garfos na ordem correta
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(second_fork);

	if (philo->last_meal == 0)
		philo->last_meal = get_current_time();
	// Seção crítica
	pthread_mutex_lock(&philo->data->write);
	if (check_sim(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->write);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d has taken a fork\n", current_time_ml(philo), philo->name);
	printf("%d %d is eating\n", current_time_ml(philo), philo->name);
	pthread_mutex_unlock(&philo->data->write);

	// Atualiza o tempo da última refeição
	//pthread_mutex_lock(&philo->data->sync);
	ft_usleep(philo, philo->data->time_eat);
	philo->last_meal = get_current_time();
	philo->eat_times++;
	//pthread_mutex_unlock(&philo->data->sync);
	// Sincroniza os dados das refeições
	pthread_mutex_lock(&philo->data->sync);
	if (philo->eat_times == philo->data->meals_number)
		philo->data->philos_finished++;
	pthread_mutex_unlock(&philo->data->sync);

	// Simula o tempo de comer

	// Libera os garfos
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}


void	ft_sleep(t_philo *philo)
{
	unsigned int finished;
	int died;
	
	pthread_mutex_lock(&philo->data->sync);
	finished = philo->data->philos_finished;
	died = philo->data->died;
	pthread_mutex_unlock(&philo->data->sync);
	//pthread_mutex_lock(&philo->data->sync);
	if (finished != philo->data->philos_num && philo->last_meal != 0 && died == 0 )
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d is sleeping\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		//pthread_mutex_unlock(&philo->data->sync);
		ft_usleep(philo, philo->data->time_sleep);
	}
	//pthread_mutex_unlock(&philo->data->sync);
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
