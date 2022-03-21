#include "philosophers.h"

int	philo_create(t_info *info, t_philos **philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	*philo = (t_philos *)malloc(sizeof(t_philos) * info->num);
	if (!*philo)
	{
		ft_putstr_fd(ER_MALLOC, STDERR_FILENO);
		return (1);
	}
	while (i < info->num)
	{
		memset(&(*philo)[i], 0, sizeof(t_philos));
		(*philo)[i].info = info;
		(*philo)[i].mut = mutex;
		(*philo)[i].id = i;
		i++;
	}
	info->philo = *philo;
	info->mut = mutex;
	return (0);
}

static int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_str_is_int(av[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

int	parser(int ac, char **av, t_info *info)
{
	if (ac < MIN_ARG || ac > MAX_ARG)
	{
		ft_putstr_fd(ER_ARG_NUM, STDERR_FILENO);
		return (1);
	}
	if (check_input(av) != 0)
	{
		ft_putstr_fd(ER_ARG_ISNINT, STDERR_FILENO);
		return (1);
	}
	info->num = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (ac == MAX_ARG)
		info->num_eat = ft_atoi(av[5]);
	if (info->num > 200 || info->t_die < 60 || info->t_eat < 60 \
		|| info->t_sleep < 60 || info->num_eat < 0)
	{
		ft_putstr_fd(ER_ARG_LIMIT, STDERR_FILENO);
		return (1);
	}
	return (0);
}
