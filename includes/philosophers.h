#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	unsigned int 			name;
	t_data			*data;
	pthread_t		id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	unsigned int	eating;
	unsigned int	ready;
	unsigned int	philos_num;
	unsigned int	meals_number;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	start_time;
} t_data;

/*   CHECK ERROR   */
int	check_args(int argc, char **argv);

/*   UTILS   */
unsigned int	ft_atoi(const char *nptr);

/*   TIME_ZONE   */
unsigned int	get_start_time();
unsigned int 	get_current_time(t_data *data);

/*   INICIALIZATION   */
int seat_the_philos(t_data *data, char **argv);

/*   ACTIONS   */
void	eat(t_philo *philo);

