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
	while ((get_current_time() - start) < milliseconds)
    {
        if ((get_current_time() - philo->last_meal) - philo->data->start_time > philo->data->time_die)
        {
            //philo->data->died = philo->name;
            return (-1);
        }
        usleep(500);
    }
	return (0);
}