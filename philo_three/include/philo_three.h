#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

typedef struct	s_table
{
	int				num_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				times_need_to_eat;
	unsigned long	start_time;
	sem_t			*fork;
	sem_t			*dead;
	sem_t			*other_died;
}				t_table;

typedef struct	s_philos
{
	int				philo_num;
	int				count_eat;
	unsigned long	last_meal;
	pid_t			pid;
	t_table			*table;
}				t_philos;

int				get_num(char *str);
int				parsing(t_table *table, char **av);

unsigned long	get_time(void);
void			my_sleep(int ms);

void		init_table_philos(t_table *table, t_philos *philos);

void		print_msg(t_philos *philo, int status, unsigned long curr_time);
void		eat(t_philos *philo);
void		*chk_philo(void *philo);
void		*chk_process(void *philo);
void		*act_philo(t_philos *philo);
int			do_situation(t_philos *philos);
void		done_situation(t_table *table, t_philos *philos);

int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
int			ft_error(char *s);

#endif