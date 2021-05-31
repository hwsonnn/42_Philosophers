/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:11:41 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:14:46 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		do_situation(t_philos *philos)
{
	int	i;
	int	status;
	int	eat;

	i = -1;
	eat = 0;
	while (++i < philos->table->num_philos)
	{
		if ((philos[i].pid = fork()) == -1)
			return (-1);
		if (philos[i].pid == 0)
			act_philo(&philos[i]);
	}
	i = -1;
	while (++i < philos->table->num_philos)
	{
		waitpid(philos[i].pid, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 0)
				eat++;
	}
	if (eat == philos->table->num_philos)
		printf("%s", "They finished all the meals.");
	return (0);
}

void	done_situation(t_table *table, t_philos *philos)
{
	sem_close(table->fork);
	sem_close(table->dead);
	sem_close(table->other_died);
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
	init_table_philos(&table, philos);
	if (do_situation(philos))
		return (ft_error("process error"));
	done_situation(&table, philos);
}
