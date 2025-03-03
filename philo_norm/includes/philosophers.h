/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miafonso <miafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:18:04 by mistery576        #+#    #+#             */
/*   Updated: 2025/01/10 15:31:01 by miafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	unsigned int	name;
	unsigned int	eat_times;
	unsigned int	last_meal;
	pthread_t		id;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	sync;
	unsigned int	died;
	unsigned int	philos_num;
	unsigned int	philos_finished;
	unsigned int	meals_number;
	unsigned int	time_think;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	start_time;
	t_philo			*philos;
}	t_data;

/*   CHECK ERROR   */
int					check_args(char **argv);
int					check_status(t_data *data);

/*   UTILS   */
unsigned int		ft_atoi(const char *nptr);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strlen(char *str);

/*   TIME_ZONE   */
unsigned int		get_current_time(void);
unsigned int		current_time_ml(t_philo *philo);
int					ft_usleep(t_philo *philo, size_t milliseconds);

/*   INICIALIZATION   */
int					seat_the_philos(t_data *data, char **argv);

/*	 ROUTINE   */
void				*routine(void *data);

/*   ACTIONS   */
void				eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				thinking(t_philo *philo);

/*   CONDITIONS   */
int					check_sim(t_philo *philo);