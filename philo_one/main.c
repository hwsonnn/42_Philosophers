/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:59:58 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:03:19 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&(table->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(table->dead));
	free(table->fork);
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
	if (init_table(&table))
		return (ft_error("malloc error"));
	init_philos(&table, philos);
	do_situation(philos);
	done_situation(&table, philos);
}
