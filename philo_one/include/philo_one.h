#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_table
{
	int				num_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				times_need_to_eat;
	int				is_philo_dead;
	unsigned long	start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t dead;
}				t_table;

typedef struct	s_philos
{
	int				philo_num;
	int				left_fork;
	int				right_fork;
	int				count_eat;
	unsigned long	last_meal;
	pthread_t		tid;
	t_table			*table;
}				t_philos;

void	*thread(void *argp);
int		get_num(char *str);
int		parsing(t_table *table, char **av);

unsigned long	get_time(void);
void		my_sleep(int ms, int is_dead);

int		init_table(t_table *table);
void	get_fork(t_philos *philo, int philo_num);
void	init_philos(t_table *table, t_philos *philos);

int		print_msg(t_philos *philo, int status, unsigned long curr_time);
int		eat(t_philos *philo);
void	*chk_philo(void *philo);
void	*act_philo(void *philo);
void	do_situation(t_philos *philos);
void	done_situation(t_table *table, t_philos *philos);

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_error(char *s);

#endif