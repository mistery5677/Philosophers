/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:35 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/03 08:49:53 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// static int	routine_validation(t_philo *philo)
// {
// 	//printf("Pilo %d vai verificar %d, finished %d philos nums %d,")
// 	// pthread_mutex_lock(&philo->data->sync);
// 	if (philo->data->died != 0 || philo->data->philos_finished == philo->data->philos_num)
// 	{
// 		//pthread_mutex_unlock(&philo->data->sync);
// 		return (2);
// 	}
// 	if (philo->data->died != 0
// 		|| philo->data->philos_finished == philo->data->philos_num
// 		|| philo->eat_times == philo->data->meals_number)
// 	{
// 		//pthread_mutex_unlock(&philo->data->sync);
// 		return (1);
// 	}
// 	//pthread_mutex_unlock(&philo->data->sync);
// 	// pthread_mutex_unlock(&philo->data->sync);
// 	return (0);
// }

int	check_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->died != 0 || philo->data->philos_finished == philo->data->philos_num)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		ft_usleep(philo, philo->data->time_eat); // Vou dar um dellay com o tempo de comer, para que o primeiro grupo de threads coma, para depois vir o proximo grupo.
	while (1)
	{
		if (check_sim(philo) == 1)
			break ;
		eat(philo);
		if (check_sim(philo) == 1)
			break ;
		ft_sleep(philo);
		if (check_sim(philo) == 1)
			break ;
		thinking(philo);
	}
	if (philo->data->died == philo->name)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d %d died\n", current_time_ml(philo), philo->name);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (NULL);
}
