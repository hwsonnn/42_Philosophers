/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:00:09 by hson              #+#    #+#             */
/*   Updated: 2021/06/18 14:57:06 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_num(char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	num = ft_atoi(str);
	if (num < 0)
		return (-1);
	else
		return (num);
}

int		parsing(t_table *table, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (i == 1 && ((table->num_philos = get_num(av[i])) == -1
				|| table->num_philos <= 1))
			return (-1);
		else if (i == 2 && (table->time_to_die = get_num(av[i])) == -1)
			return (-1);
		else if (i == 3 && (table->time_to_eat = get_num(av[i])) == -1)
			return (-1);
		else if (i == 4 && (table->time_to_sleep = get_num(av[i])) == -1)
			return (-1);
		else if (i == 5 && (table->times_need_to_eat = get_num(av[i])) == -1)
			return (-1);
		i++;
	}
	if (i == 5)
		table->times_need_to_eat = -1;
	return (0);
}

int		init_table(t_table *table)
{
	int	i;

	i = 0;
	table->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
										* table->num_philos);
	if (!(table->fork))
		return (-1);
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->dead, NULL);
	pthread_mutex_init(&table->msg, NULL);
	table->is_philo_dead = 0;
	table->start_time = get_time();
	return (0);
}

void	get_fork(t_philos *philo, int philo_num)
{
	if (philo_num == 0)
		philo->left_fork = philo->table->num_philos - 1;
	else
		philo->left_fork = philo_num - 1;
	philo->right_fork = philo_num;
}

void	init_philos(t_table *table, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		philos[i].philo_num = i;
		philos[i].table = table;
		get_fork(&philos[i], i);
		philos[i].count_eat = 0;
		i++;
	}
}
