/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:08:36 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:09:59 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	do_situation(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->num_philos)
	{
		philos[i].last_meal = get_time();
		pthread_create(&(philos[i].tid), NULL, act_philo, &philos[i]);
		i++;
	}
	i = 0;
	while (i < philos->table->num_philos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
}

void	done_situation(t_table *table, t_philos *philos)
{
	sem_close(table->fork);
	sem_close(table->dead);
	free(philos);
}

int		main(int argc, char **argv)
{
	t_table		table;
	t_philos	*philos;

	if (argc < 5 || argc > 6)
		return (ft_error("argc error"));
	if (parsing(&table, argv))
		return (ft_error("parsing error"));
	philos = (t_philos *)malloc(sizeof(t_philos) * table.num_philos);
	if (!philos)
		return (ft_error("malloc error"));
	init_table(&table);
	init_philos(&table, philos);
	do_situation(philos);
	done_situation(&table, philos);
}
