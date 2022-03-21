#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	sleep_wrapper(uint64_t time)
{
	uint64_t	ms;

	ms = gettime_ms();
	while (1)
	{
		if (gettime_ms() - ms >= time)
			break ;
		usleep(100);
	}
}
