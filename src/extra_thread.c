#include "philosophers.h"

int	error_handle(pthread_mutex_t *write, pthread_mutex_t *death, char *msg)
{
	if (write)
		pthread_mutex_lock(write);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (death)
		pthread_mutex_unlock(death);
	return (1);
}

int	left(int id)
{
	return (id);
}

int	right(int id, int num)
{
	return ((id + 1) % num);
}

static char	*message_extra(t_status stat)
{
	if (stat == E_FORK)
		return (M_FORK);
	else if (stat == E_THINK)
		return (M_THINK);
	else if (stat == E_EAT)
		return (M_EAT);
	else if (stat == E_SLEEP)
		return (M_SLEEP);
	return (M_DIE);
}

void	message(t_philos *philo, t_status stat)
{
	uint64_t	ms;

	ms = gettime_ms();
	ms = ms - philo->t_start;
	pthread_mutex_lock(&philo->mut->message[0]);
	printf("%llu %d %s\n", ms, philo->id + 1, message_extra(stat));
	if (stat == E_DIE)
		return ;
	pthread_mutex_unlock(&philo->mut->message[0]);
}
