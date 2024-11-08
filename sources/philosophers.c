/* number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat] */
#include "../includes/philosophers.h"

// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

// void	routine()

void	print_info(t_data *data) //Debug function
{
	printf("Start Time %d\n", data->start_time);
	printf("Philos num %d\n", data->philos_num);
	printf("Time to die %d\n", data->time_die);
	printf("Time to eat %d\n", data->time_eat);
	printf("Time to sleep %d\n", data->time_sleep);
	printf("Meals to eat %d\n", data->meals_number);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (check_args(argc, argv) == -1)
		return (-1);
	if (seat_the_philos(&data, argv) == -1)
		return (-1);
	data.philos[0].name = 1;
	printf("data.philo[0].name = %d\n", data.philos[0].name);
	//print_info(&data);
	
	/*TESTAR O TEMPO DE EXECUCAO*/
	// printf("Time %d\n", philos.start_time);
	// usleep(2000);
	// get_current_time(&(philos).start_time);
	//printf("Time %d\n",philos.start_time);
	//printf("die %d\neat %d\nsleep %d\n", philos.time_die, philos.time_eat, philos.time_sleep);
}
