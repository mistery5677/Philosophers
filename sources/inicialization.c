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

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	printf("Philo %d\n", philo->name);
	return NULL;
}

int seat_the_philos(t_data *data, char **argv)
{
	unsigned int i;

	i = 0;
	data->philos_num = ft_atoi(argv[1]);
	printf("temos %d filosofos\n", data->philos_num);
	data->philos = malloc((data->philos_num) * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_number = ft_atoi(argv[5]);
	else
		data->meals_number = -1;
	get_current_time(&(data)->start_time);
	data->forks = malloc(data->philos_num * sizeof(pthread_mutex_t));
	while (i < data->philos_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[data->philos_num - 1];
	i++;
	while (i < data->philos_num)
	{
		//printf("entrou\n");
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i - 1];
		i++;
	}
	// printf("r_fork %p\nl_fork %p\n", data->philos[0].r_fork, data->philos[0].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[1].r_fork, data->philos[1].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[2].r_fork, data->philos[2].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[3].r_fork, data->philos[3].l_fork);
	i = 0;
	while (i < data->philos_num)
	{
		printf("Criou um thread\n");
		data->philos[i].name = i + 1;
		if (pthread_create(&data->philos[i].id, NULL, routine, &data->philos[i]) == -1)
			return (-1);
		 usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->philos_num)
	{
		pthread_join(data->philos[i].id, NULL);
		i++;
	}
	return 0;
}