#include "philosophers.h"

uint64_t	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	mutex_init(pthread_mutex_t *mut_forks, int mutex_num)
{
	int	i;

	i = 0;
	while (i < mutex_num)
	{
		if (pthread_mutex_init(&mut_forks[i], NULL) != 0)
		{
			ft_putstr_fd(ER_MUTEX_INIT, STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	mutexs_init(t_mutex *mutex, t_info *info)
{
	if (mutex_init(mutex->forks, info->num) != 0)
		return (1);
	if (mutex_init(mutex->message, 1) != 0)
		return (1);
	if (mutex_init(mutex->shared, 1) != 0)
		return (1);
	return (0);
}

static void	mutex_destroy(pthread_mutex_t *mut_forks, int mutex_num)
{
	int	i;

	i = 0;
	while (i < mutex_num)
	{
		pthread_mutex_destroy(&mut_forks[i]);
		i++;
	}
}

void	mutexs_destroy(t_mutex *mutex, t_info *info)
{
	mutex_destroy(mutex->forks, info->num);
	mutex_destroy(mutex->message, 1);
	mutex_destroy(mutex->shared, 1);
}
