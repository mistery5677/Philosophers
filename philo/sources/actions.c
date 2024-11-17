#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->mut_dead); //To sinc the data, when the time to eat is lower than time to die
	if (philo->data->died != 0)
	{
		pthread_mutex_unlock(&philo->data->mut_dead);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return;
	}
	pthread_mutex_unlock(&philo->data->mut_dead);
	printf("%d %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->name);
	printf("%d %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->name);
	printf("%d %d is eating\n", get_current_time() - philo->data->start_time, philo->name);
	philo->last_meal = get_current_time();
	if (ft_usleep(philo, philo->data->time_eat) == -1 && philo->data->died == 0)
	{
		//philo->data->died = philo->name;
		//printf("%d %d died\n", get_current_time() - philo->data->start_time, philo->name);
	}
	philo->eat_times++;
	//pthread_mutex_lock(&philo->data->mut_dead);
	//pthread_mutex_unlock(&philo->data->mut_dead);
	pthread_mutex_lock(&philo->data->mut_dead);
	if (philo->eat_times == philo->data->meals_number)
		philo->data->philos_finished++;
	pthread_mutex_unlock(&philo->data->mut_dead);
	philo->last_meal = get_current_time();
	//printf("ocurrent time %d\n", get_current_time(philo->data));
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->data->philos_finished != philo->data->philos_num)
	{
		printf("%d %d is sleeping\n", get_current_time() - philo->data->start_time, philo->name);
		//printf("Vou dormir %d com %d filosofos satisfeitos de %d meals\n", philo->name, philo->data->philos_finished, philo->data->meals_number);
		ft_usleep(philo, philo->data->time_sleep);
	}
	// if (ft_usleep(philo, philo->data->time_sleep) == -1 && philo->data->died != 0)
	// 	printf("%d %d died\n", get_current_time() - philo->data->start_time, philo->name);
}

void thinking(t_philo *philo)
{
	if (philo->data->time_think != 0)
	{
		printf("%d %d is thinking\n", get_current_time() - philo->data->start_time, philo->name);
		ft_usleep(philo, philo->data->time_think);
		// if (ft_usleep(philo, philo->data->time_sleep) == -1 && philo->data->died != 0)
		// 	printf("%d %d died\n", get_current_time() - philo->data->start_time, philo->name);
	}
}

// t2 60.2 -> 120.8
// t4 60.7 -> 120.6 ++filosofos_finished --> finished < 