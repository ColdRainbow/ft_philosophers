#include "philosophers.h"

static void	philo_actions_take_forks(t_philos *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&philo->mut->forks[left(philo->id)]);
	else
		pthread_mutex_lock(&philo->mut->forks[right(philo->id, \
		philo->info->num)]);
	message(philo, E_FORK);
	if (philo->id % 2)
		pthread_mutex_lock(&philo->mut->forks[right(philo->id, \
			philo->info->num)]);
	else
		pthread_mutex_lock(&philo->mut->forks[left(philo->id)]);
	message(philo, E_FORK);
}

static void	philo_actions_put_forks(t_philos *philo)
{
	if (philo->id % 2)
		pthread_mutex_unlock(&philo->mut->forks[right(philo->id, \
			philo->info->num)]);
	else
		pthread_mutex_unlock(&philo->mut->forks[left(philo->id)]);
	if (philo->id % 2)
		pthread_mutex_unlock(&philo->mut->forks[left(philo->id)]);
	else
		pthread_mutex_unlock(&philo->mut->forks[right(philo->id, \
		philo->info->num)]);
}

static void	philo_actions_eat(t_philos *philo)
{
	philo->t_last_eat = gettime_ms();
	message(philo, E_EAT);
	philo->eaten++;
	if (philo->info->num_eat && philo->eaten == philo->info->num_eat)
	{
		pthread_mutex_lock(&philo->mut->shared[0]);
		philo->info->num_eaten++;
		pthread_mutex_unlock(&philo->mut->shared[0]);
	}
	sleep_wrapper(philo->info->t_eat);
}

static void	philo_actions_sleep_think(t_philos *philo)
{
	message(philo, E_SLEEP);
	sleep_wrapper(philo->info->t_sleep);
	message(philo, E_THINK);
}

void	philo_actions(t_philos *philo)
{
	philo_actions_take_forks(philo);
	philo_actions_eat(philo);
	philo_actions_put_forks(philo);
	philo_actions_sleep_think(philo);
}
