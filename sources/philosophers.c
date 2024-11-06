/* number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat] */
#include "../includes/philosophers.h"

// size_t	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

int	main(int argc, char **argv)
{
	t_philo philos;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		write (2, "Wrong number of arguments\n", 26);
		return (-1);
	}
	else if (check_argv(argv) == -1)
	{
		write (2, "Bad input\n", 10);
		return (-1);
	}
	else if (ft_strcmp(argv[1], "200") > 0)
	{
		write (2, "Max limit of philo\n", 19);
		return (-1);
	}
	seat_the_philos(&philos, argv);
	printf("Time %d\n", philos.start_time);
	usleep(2000);
	get_current_time(&(philos).start_time);
	printf("Time %d\n",philos.start_time);
	//printf("die %d\neat %d\nsleep %d\n", philos.time_die, philos.time_eat, philos.time_sleep);
}
