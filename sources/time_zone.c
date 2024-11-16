#include "../includes/philosophers.h"

unsigned int get_current_time()
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
    {
        write(2, "gettimeofday() error\n", 22);
        return (-1);
    }
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
    //printf("last meal %d\n", philo->last_meal);
	while ((get_current_time() - start) < milliseconds)
    {
        //printf("philo name %d     current_time() - philo->last_meal %d\n", philo->name, get_current_time() - philo->last_meal);
        pthread_mutex_lock(&philo->data->mut_dead);
        if (philo->last_meal != 0 && philo->data->died == 0 && (get_current_time() - philo->last_meal) > philo->data->time_die)
        {
            //printf("Alguém morreu\n");
            philo->data->died = philo->name;
            //printf("Morreu %d\n", get_current_time() - philo->last_meal);
            //printf("Philo %d (get_current_time() - philo->last_meal) - philo->data->start_time %d philo->data->time_die %d\n", philo->name, (get_current_time() - philo->last_meal) - philo->data->start_time, philo->data->time_die);
            pthread_mutex_unlock(&philo->data->mut_dead);
            return (-1);
        }
        pthread_mutex_unlock(&philo->data->mut_dead);
        usleep(500);
    }
	return (0);
}