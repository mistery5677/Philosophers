#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	unsigned int 	name;
	unsigned int	eat_times;
	unsigned int	last_meal;
	t_data			*data;
	pthread_t		id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	//pthread_mutex_t *mut_dead;
	unsigned int	died;
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
unsigned int 	get_current_time();
int	ft_usleep(t_philo *philo, size_t milliseconds);

/*   INICIALIZATION   */
int seat_the_philos(t_data *data, char **argv);

/*	 ROUTINE   */
void	*routine(void *data);

/*   ACTIONS   */
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void 	thinking();

