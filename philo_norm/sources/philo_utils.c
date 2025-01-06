/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:00:44 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/06 23:21:21 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned int	ft_atoi(const char *nptr)
{
	unsigned long int	final_nr;
	unsigned int		i;

	final_nr = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		final_nr = (final_nr * 10) + (nptr[i] - '0');
		i++;
	}
	return (final_nr);
}
