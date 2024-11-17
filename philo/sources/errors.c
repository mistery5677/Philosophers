#include "../includes/philosophers.h"

static int	check_argv(char **argv)
{
	int	i;
	int	x;

	i = 1;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
				return (-1);
			x++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
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
	else if (ft_atoi(argv[1]) > 200)
	{
		write (2, "Max limit of philo\n", 19);
		return (-1);
	}
	return (0);
}