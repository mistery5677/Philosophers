#include "../includes/philosophers.h"

int	check_argv(char **argv)
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

int ft_strcmp(char *s1, char *s2)
{
        int i;

        i = 0;
        //printf("s1 %s s2 %s\n", s1, s2);
        if (!s1 || !s2)
        {
                printf("s1 or s2 are empty\n");
                return (-1);
        }
        while(s1[i] || s2[i])
        {
                if (s1[i] != s2[i])
                        return (s1[i] - s2[i]);
                i++;
        }
        return (0);
}
