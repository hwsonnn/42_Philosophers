/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:12:06 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:14:23 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*chk_philo(void *philo)
{
	t_philos	*phi;

	phi = (t_philos *)philo;
	while (1)
	{
		if (phi->count_eat == phi->table->times_need_to_eat)
			exit(0);
		if (get_time() - phi->last_meal > phi->table->time_to_die)
		{
			sem_wait(phi->table->dead);
			print_msg(phi, DIED, get_time());
			sem_post(phi->table->other_died);
			exit(1);
		}
		my_sleep(1);
	}
	return (0);
}

void	*chk_process(void *philo)
{
	t_philos *phi;

	phi = (t_philos *)philo;
	sem_wait(phi->table->other_died);
	sem_post(phi->table->other_died);
	exit(1);
	return (0);
}

void	eat(t_philos *philo)
{
	sem_wait(philo->table->fork);
	print_msg(philo, FORK, get_time());
	sem_wait(philo->table->fork);
	print_msg(philo, FORK, get_time());
	print_msg(philo, EAT, get_time());
	philo->last_meal = get_time();
	my_sleep(philo->table->time_to_eat);
	sem_post(philo->table->fork);
	sem_post(philo->table->fork);
	philo->count_eat += 1;
}

void	*act_philo(t_philos *philo)
{
	pthread_t	tid1;
	pthread_t	tid2;

	philo->last_meal = get_time();
	pthread_create(&tid1, NULL, chk_philo, philo);
	pthread_create(&tid2, NULL, chk_process, philo);
	if (philo->philo_num % 2 == 0)
		my_sleep(1);
	while (1)
	{
		eat(philo);
		print_msg(philo, SLEEP, get_time());
		my_sleep(philo->table->time_to_sleep);
		print_msg(philo, THINK, get_time());
	}
	pthread_join(tid1, NULL);
	return (0);
}
