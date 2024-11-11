#include "../includes/philosophers.h"

unsigned int get_start_time()
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
    {
        write(2, "gettimeofday() error\n", 22);
        return (-1);
    }
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned int get_current_time(t_data *data)
{
    unsigned int current_time = get_start_time();
    return (current_time - data->start_time);
}