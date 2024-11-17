#include "../includes/philosophers.h"

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	//printf("id = %d | resultado = %d", philo->name)
	if(philo->name % 2 == 0)
		usleep(1000);
	//printf("eating %d\n", philo->data->eating);
	//printf("Philo name %d morreu o %d\n", philo->name, philo->data->died);
	//while (philo->eat_times < philo->data->meals_number)
	while(1)
	{
		//pthread_mutex_lock(&philo->data->sync);
		if (philo->data->died != 0 || philo->data->philos_finished == philo->data->philos_num || philo->eat_times == philo->data->meals_number)
		{
			//printf("breaked\n");
			//pthread_mutex_unlock(&philo->data->sync);
			break;
		}
		//pthread_mutex_unlock(&philo->data->sync);

		eat(philo);

		//pthread_mutex_lock(&philo->data->sync);
		if (philo->data->died != 0 || philo->data->philos_finished == philo->data->philos_num)
		{
			//printf("breaked\n");
			//pthread_mutex_unlock(&philo->data->sync);
			break;
		}
		//pthread_mutex_unlock(&philo->data->sync);

		ft_sleep(philo);

		//pthread_mutex_lock(&philo->data->sync);
		if (philo->data->died != 0 || philo->data->philos_finished == philo->data->philos_num)
		{
			//printf("breaked\n");
			//pthread_mutex_unlock(&philo->data->sync);
			break;
		}
		//pthread_mutex_unlock(&philo->data->sync);

		// printf("Time think %d  finished %d philos_num %d", philo->data->time_think, philo->data->philos_finished, philo->data->philos_num);
		if (philo->data->time_think > 0 || philo->data->philos_finished != philo->data->philos_num)
			thinking(philo);
	}
	//printf("Philo satisfeitos %d\n", philo->data->philos_finished);
	if (philo->name == philo->data->died)
		printf("%d %d died\n", get_current_time() - philo->data->start_time, philo->data->died);
	// if (philo->data->died != 0)
	// 	printf("%d %d died\n", get_current_time() - philo->data->start_time, philo->data->died);
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