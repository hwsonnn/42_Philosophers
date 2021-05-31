/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:12:02 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:13:00 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		if (i == 1 && (table->num_philos = get_num(av[i])) == -1)
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

void	init_table_philos(t_table *table, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		philos[i].philo_num = i;
		philos[i].table = table;
		philos[i].count_eat = 0;
		i++;
	}
	sem_unlink("/fork");
	sem_unlink("/dead");
	sem_unlink("/other_died");
	table->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, table->num_philos);
	table->dead = sem_open("/dead", O_CREAT | O_EXCL, 0644, 1);
	table->other_died = sem_open("/other_died", O_CREAT | O_EXCL, 0644, 0);
	table->start_time = get_time();
}
