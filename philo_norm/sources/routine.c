/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:35 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/20 01:14:28 by mistery576       ###   ########.fr       */
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->data->sim == 1)
			break ;
		eat(philo);
		if (philo->data->sim == 1)
			break ;
		ft_sleep(philo);
		if (philo->data->sim == 1)
			break ;
		if (philo->data->time_think > 0)
			thinking(philo);
	}
	if (philo->name == philo->data->died)
		printf("%d %d died\n", current_time_ml(philo), philo->data->died);
	return (NULL);
}
