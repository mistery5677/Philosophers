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
    {
	    start_time = current_time;
	}
   	*execute_time = (current_time - start_time) * 1000;
}

void	*hello_world(void *arg)
{
	(void)arg;
	printf("hello world");
	return NULL;
}

int seat_the_philos(t_data *data, char **argv)
{
	unsigned int i;

	i = 0;
	data->philos_num = ft_atoi(argv[1]);
	data->t_philo = malloc(data->philos_num * sizeof(pthread_t));
	if (!data->philos)
		return (-1);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->philos = malloc(data->philos_num * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	if (argv[5])
		data->meals_number = ft_atoi(argv[5]);
	else
		data->meals_number = 1;
	get_current_time(&(data)->start_time);
	while (i < data->philos_num)
	{
		printf("Criou um thread\n");
		if (pthread_create(&data->t_philo[i], NULL, hello_world, NULL) == -1)
			return (-1);
		i++;
	}
	return 0;
}