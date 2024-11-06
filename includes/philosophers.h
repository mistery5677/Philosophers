#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		t_philo;
	int name;
} t_philo;

typedef struct s_data
{
	pthread_t		*t_philo;
	t_philo			*philos;
	unsigned int	meals_number;
	unsigned int	philos_num;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	start_time;
} t_data;

/*   CHECK ERROR   */
int	check_args(int argc, char **argv);

/*   INICIALIZATION   */
unsigned int	ft_atoi(const char *nptr);
int seat_the_philos(t_data *data, char **argv);
void get_current_time(unsigned int *execute_time);

/*   */
