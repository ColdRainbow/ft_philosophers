#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

# define MIN_ARG		5
# define MAX_ARG		6
# define MAX_PHILO_NUM	200

# define MIN_INT		"-2147483648"
# define MAX_INT		"2147483647"
# define MAX_INT_P		"+2147483647"

# define M_FORK			"has taken a fork"
# define M_THINK		"is thinking"
# define M_EAT			"is eating"
# define M_SLEEP		"is sleeping"
# define M_DIE			"died"

# define ER_ARG_ISNINT	"Error: some argument is not a number\n"
# define ER_ARG_NUM		"Error: wrong number of arguments\n"
# define ER_ARG_LIMIT	"Error: arg value is greater or less than the desired\n"
# define ER_MALLOC		"Error: malloc()\n"
# define ER_MUTEX_INIT	"Errror: pthread_mutex_init()\n"
# define ER_MUTEX_DEST	"Errror: pthread_mutex_destroy()\n"
# define ER_PTHR_CREATE	"Error: pthread_create()\n"

typedef enum e_status
{
	E_FORK,
	E_THINK,
	E_EAT,
	E_SLEEP,
	E_DIE
}	t_status;

typedef struct s_mutex
{
	pthread_t		thr_id[MAX_PHILO_NUM];
	pthread_mutex_t	forks[MAX_PHILO_NUM];
	pthread_mutex_t	message[1];
	pthread_mutex_t	shared[1];
}	t_mutex;

typedef struct s_info
{
	int				num;
	uint64_t		t_die;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				num_eat;

	int				num_eaten;

	struct s_mutex	*mut;
	struct s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	uint64_t		t_start;
	uint64_t		t_last_eat;
	int				eaten;

	struct s_info	*info;
	t_mutex			*mut;
}	t_philos;

// parser, init
int			parser(int ac, char **av, t_info *info);
int			philo_create(t_info *info, t_philos **philo, t_mutex *mutex);

// lib functions
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			check_str_is_int(char *str);
int			ft_strncmp(const char *str1, const char *str2, size_t num);

// extra functions
uint64_t	gettime_ms(void);
int			mutexs_init(t_mutex *mutex, t_info *info);
void		mutexs_destroy(t_mutex *mutex, t_info *info);

// thread functions
void		philo_actions(t_philos *philo);
void		sleep_wrapper(uint64_t time);
int			left(int id);
int			right(int id, int num);
void		message(t_philos *philo, t_status stat);
int			error_handle(pthread_mutex_t *write, \
							pthread_mutex_t *death, char *msg);

#endif
