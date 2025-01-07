/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mistery576 <mistery576@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:37:22 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/07 00:13:37 by mistery576       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_argv(char **argv)
{
	int	i;
	int	x;

	i = 1;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
				return (-1);
			x++;
		}
		i++;
	}
	return (0);
}

static void	check_limits(char **argv)
{
	int	i;

	i = 2;
	if (ft_strlen(argv[1]) > 3 || ft_strncmp(argv[1], "200", 3) > 0)
	{
		write (2, "Max limit of philo\n", 19);
		exit(1);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10
			|| ft_strncmp(argv[i], "2147483647", 10) > 0)
		{
			write (2, "Too big number\n", 15);
			exit(1);
		}
		i++;
	}
}

int	check_args(int argc, char **argv)
{
	check_limits(argv);
	if (argc < 5 || argc > 6)
	{
		write (2, "Wrong number of arguments\n", 26);
		return (-1);
	}
	else if (check_argv(argv) == -1)
	{
		write (2, "Bad input\n", 10);
		return (-1);
	}
	return (0);
}

int	check_status(t_data *data)
{
	if (data->philos_num == 0)
	{
		printf("No philos to seat\n");
		return (-1);
	}
	if (data->time_die == 0 || data->time_eat == 0 || data->time_sleep == 0)
	{
		printf("0 seconds is impossible\n");
		return (-1);
	}
	return (0);
}
