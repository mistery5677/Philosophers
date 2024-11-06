#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	unsigned int	philos;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	start_time;
} t_philo;

/*   CHECK ERROR   */
int	check_argv(char **argv);
int ft_strcmp(char *s1, char *s2);

/*   INICIALIZATION   */
unsigned int	ft_atoi(const char *nptr);
void seat_the_philos(t_philo *philo, char **argv);
void get_current_time(unsigned int *execute_time);

/*   */
