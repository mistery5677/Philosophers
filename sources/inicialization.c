#include "../includes/philosophers.h"

unsigned int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	unsigned int	final_nr;

	neg = 1;
	final_nr = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		final_nr = (final_nr * 10) + (nptr[i] - '0');
		i++;
	}
	return (final_nr * neg);
}

void get_current_time(unsigned int *execute_time)
{
    static size_t start_time;
    struct timeval time;
	size_t current_time;

    if (gettimeofday(&time, NULL) == -1)
    {
        write(2, "gettimeofday() error\n", 22);
        return ;
    }
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
    if (start_time == 0)
        start_time = current_time;
   	*execute_time = (current_time - start_time) * 1000;
}

void seat_the_philos(t_philo *philo, char **argv)
{
	philo->philos = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	get_current_time(&(philo)->start_time);
}