#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%d %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->name);
	pthread_mutex_lock(philo->l_fork);
	printf("%d %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->name);
	printf("%d %d is eating\n", get_current_time() - philo->data->start_time, philo->name);
	philo->eat_times++;
	ft_usleep(philo->data->time_eat);
	//printf("ocurrent time %d\n", get_current_time(philo->data));
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	printf("%d %d is sleeping\n", get_current_time() - philo->data->start_time, philo->name);
	ft_usleep(philo->data->time_sleep);
}

void thinking(t_philo *philo)
{
	if (philo->data->time_eat > philo->data->time_sleep)
	{
		printf("%d %d is thinking\n", get_current_time() - philo->data->start_time, philo->name);
		ft_usleep(philo->data->time_eat - philo->data->time_sleep);
	}
}