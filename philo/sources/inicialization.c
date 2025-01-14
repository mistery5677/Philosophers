#include "../includes/philosophers.h"

static void get_think(t_data *data)
{
	if (data->philos_num % 2 == 0)
	{
		if (data->time_eat > data->time_sleep)
			data->time_think = data->time_eat - data->time_sleep;
		else 
			data->time_think = 0;
	}
	else 
	{
		if (data->time_eat * 2 > data->time_sleep)
			data->time_think = (data->time_eat * 2) - data->time_sleep;
		else 
			data->time_think = 0;
	}
}

static int initialize_status(t_data *data, char **argv)
{
	data->philos_num = ft_atoi(argv[1]);
	printf("temos %d filosofos\n", data->philos_num);
	data->philos = malloc((data->philos_num) * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	get_think(data);
	if (argv[5])
		data->meals_number = ft_atoi(argv[5]);
	else
		data->meals_number = -1;  //Tenho de mudar antes de entregar o projeto
	data->philos_finished = 0;
	data->start_time = get_current_time();
	data->died = 0;
	return (0);
}

static int initialize_mutex(t_data *data)
{
	unsigned int i;

	i = 0;
	pthread_mutex_init(&data->sync, NULL);
	if (pthread_mutex_init(&data->mut_dead, NULL) != 0)
		return (-1);
	data->forks = malloc(data->philos_num * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (-1);
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (-1);
		i++;
	}
	i = 0;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[data->philos_num - 1];
	i++;
	while (i < data->philos_num)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

static int born_philos(t_data *data)
{
	unsigned int i;

	i = 0;
	pthread_create(*data->supervisor, NULL, conditions, &data);
	while (i < data->philos_num)
	{
		//printf("Criou um thread\n");
		data->philos[i].name = i + 1;
		data->philos[i].data = data;
		//data->ready++;
		if (pthread_create(&data->philos[i].id, NULL, routine, &data->philos[i]) == -1)
			return (-1);
		//usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_join(data->philos[i].id, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static void obliterate_table(t_data *data)
{
	unsigned int i;

	i = 0;
	while(i < data->philos_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mut_dead);
	pthread_mutex_destroy(&data->sync);
}

int seat_the_philos(t_data *data, char **argv)
{
	if (initialize_status(data, argv) == -1)
		return (-1);
	//printf("start time %d | 	\n", data->start_time);
	//printf("A simulacao comecou %d\n", data->start_time);



	/*    MUTEX INICIALIZATION   */

	if (initialize_mutex(data) == -1)
		return (-1);

	// printf("r_fork %p\nl_fork %p\n", data->philos[0].r_fork, data->philos[0].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[1].r_fork, data->philos[1].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[2].r_fork, data->philos[2].l_fork);
	// printf("r_fork %p\nl_fork %p\n", data->philos[3].r_fork, data->philos[3].l_fork);
	
	
	
	/*   THREAD INICIALIZATION   */

	if (born_philos(data) == -1)
		return (-1);
	
	//pthread_mutex_destroy(&data->mut_dead);
	
	/*   THREAD DESTRUCTION   */

	obliterate_table(data);
	return 0;
}

