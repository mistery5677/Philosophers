#include "../includes/philosophers.h"

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	while (philo->id % 2 == 0 && philo->data->eating < philo->data->philos_num / 2)
	{
		//printf("eating %d\n", philo->data->eating);
		continue ;
	}
	printf("eating %d\n", philo->data->eating);
	eat(philo);

	//    FORMA DE ORDENAR AS THREADS
	// while(philo->data->philos_num + 1 != philo->data->ready) // Temos de colocar o +1 por causa da ultima incrementacao
	// {
	// 	//printf("philo name %d    ready %d\n", philo->name, philo->data->ready);
	// 	if (philo->name == philo->data->ready)
	// 	{
	// 		printf("seated %d\n", philo->name);
	// 		philo->data->ready++;
	// 		break ;
	// 	}
	// 	continue ;
	// }
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
	data->ready = 1;
	if (argv[5])
		data->meals_number = ft_atoi(argv[5]);
	else
		data->meals_number = -1;
	data->eating = 0;
	data->start_time = get_start_time();
	//printf("A simulacao comecou %d\n", data->start_time);



	/*    MUTEX INICIALIZATION   */



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
	
	
	
	/*   THREAD INICIALIZATION   */

	
	
	i = 0;
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
		pthread_join(data->philos[i].id, NULL);
		i++;
	}
	return 0;
}