/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:28:14 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/05 20:44:31 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	pick_forks(t_philo *philo,
		pthread_mutex_t **fork1, pthread_mutex_t **fork2)
{
	if (philo->r_fork < philo->l_fork)
	{
		*fork1 = philo->r_fork;
		*fork2 = philo->l_fork;
	}
	else
	{
		*fork1 = philo->l_fork;
		*fork2 = philo->r_fork;
	}
	pthread_mutex_lock(*fork1);
	pthread_mutex_lock(*fork2);
	if (philo->last_meal == 0)
		philo->last_meal = get_current_time();
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	pick_forks(philo, &first_fork, &second_fork);
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
	ft_usleep(philo, philo->data->time_eat);
	philo->last_meal = get_current_time();
	philo->eat_times++;
	pthread_mutex_lock(&philo->data->sync);
	if (philo->eat_times == philo->data->meals_number)
		philo->data->philos_finished++;
	pthread_mutex_unlock(&philo->data->sync);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	ft_sleep(t_philo *philo)
{
	unsigned int	finished;
	int				died;

	pthread_mutex_lock(&philo->data->sync);
	finished = philo->data->philos_finished;
	died = philo->data->died;
	pthread_mutex_unlock(&philo->data->sync);
	if (finished != philo->data->philos_num
		&& philo->last_meal != 0 && died == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d is sleeping\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_sleep);
	}
}

void	thinking(t_philo *philo)
{
	unsigned int	finished;
	int				died;

	pthread_mutex_lock(&philo->data->sync);
	finished = philo->data->philos_finished;
	died = philo->data->died;
	pthread_mutex_unlock(&philo->data->sync);
	if (philo->data->time_think != 0
		&& died == 0 && finished != philo->data->philos_num)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d is thinking\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_think);
	}
}
