#include "../includes/philosophers.h"

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	//printf("id = %d | resultado = %d", philo->name)
	if(philo->name % 2 == 0)
		usleep(1000);
	//printf("eating %d\n", philo->data->eating);
	printf("Philo name %d morreu o %d\n", philo->name, philo->data->died);
	while (philo->eat_times < philo->data->meals_number && philo->data->died == 0)
	{
		if (philo->data->died != 0)
		{
			//printf("breaked\n");
			break;
		}
		eat(philo);
		if (philo->data->died != 0)
		{
			//printf("breaked\n");
			break;
		}
		ft_sleep(philo);
		if (philo->data->died != 0)
		{
			//printf("breaked\n");
			break;
		}
		if (philo->data->time_think > 0)
			thinking(philo);
	}
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