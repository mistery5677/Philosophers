/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:35 by mistery576        #+#    #+#             */
/*   Updated: 2024/11/24 21:23:43 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		ft_usleep(philo, philo->data->time_eat);
	while (1)
	{
		if (philo->data->sim == 1)
			break ;
		eat(philo);
		if (philo->data->died != 0)
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
