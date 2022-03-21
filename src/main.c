#include "philosophers.h"

void	philo_lifetime(t_info *info)
{
	int			i;
	uint64_t	ms;

	while (1)
	{
		i = 0;
		ms = gettime_ms();
		while (i < info->num)
		{
			if (ms > info->philo[i].t_last_eat + info->t_die && \
				info->philo[i].t_last_eat != 0)
			{
				message(&info->philo[i], E_DIE);
				return ;
			}
			if (info->num_eat && info->num_eaten == info->num)
			{
				pthread_mutex_lock(&info->mut->message[0]);
				return ;
			}
			usleep(100);
			i++;
		}
	}
}

static void	*thread_philo(void *_philo)
{
	t_philos	*philo;

	philo = (t_philos *)_philo;
	philo->t_last_eat = gettime_ms();
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		philo_actions(philo);
	}
	return (NULL);
}

static int	thread_init(t_mutex *mutex, t_info *info, t_philos *philo)
{
	int			i;
	uint64_t	t_start;

	i = 0;
	t_start = gettime_ms();
	while (i < info->num)
	{
		philo[i].t_start = t_start;
		if (pthread_create(&mutex->thr_id[i], NULL, thread_philo, &philo[i]) \
				!= 0)
		{
			ft_putstr_fd(ER_PTHR_CREATE, STDERR_FILENO);
			return (1);
		}
		pthread_detach(mutex->thr_id[i]);
		i++;
	}
	philo_lifetime(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_mutex			mutex;
	t_info			info;
	t_philos		*philo;

	memset(&info, 0, sizeof(t_info));
	if (parser(ac, av, &info) != 0)
		return (1);
	if (philo_create(&info, &philo, &mutex) != 0)
		return (1);
	if (mutexs_init(&mutex, &info) != 0)
		return (1);
	if (thread_init(&mutex, &info, philo) != 0)
		return (1);
	mutexs_destroy(&mutex, &info);
	free(philo);
	return (0);
}
