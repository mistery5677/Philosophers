#include "../includes/philosophers.h"

void	*routine(void *data)
{
	t_philo *philo = (t_philo *)data;

	//printf("id = %d | resultado = %d", philo->name)
	if(philo->name % 2 == 0)
		usleep(1000);
	//printf("eating %d\n", philo->data->eating);
	while (philo->eat_times < philo->data->meals_number)
	{
		eat(philo);
		ft_sleep(philo);
		thinking(philo);
	}

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