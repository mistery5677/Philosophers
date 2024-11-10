#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	
	pthread_mutex_lock(philo->r_fork);
	printf("%d %d has taken a fork\n", get_current_time(philo->data), philo->name);
	pthread_mutex_lock(philo->l_fork);
	printf("%d %d has taken a fork\n", get_current_time(philo->data), philo->name);
	printf("%d %d is eating\n", get_current_time(philo->data), philo->name);
	philo->data->eating++;
	usleep(philo->data->time_eat);
	printf("ocurrent time %d\n", get_current_time(philo->data));
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}