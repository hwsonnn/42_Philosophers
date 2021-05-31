/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:08:43 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:10:39 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*chk_philo(void *philo)
{
	t_philos	*phi;

	phi = (t_philos *)philo;
	while (1)
	{
		if (phi->count_eat == phi->table->times_need_to_eat)
			break ;
		if (get_time() - phi->last_meal > phi->table->time_to_die)
		{
			sem_wait(phi->table->dead);
			if (print_msg(phi, DIED, get_time()))
			{
				sem_post(phi->table->dead);
				break ;
			}
			phi->table->is_philo_dead = 1;
			sem_post(phi->table->dead);
			break ;
		}
		my_sleep(1, phi->table->is_philo_dead);
	}
	return (0);
}

int		eat(t_philos *philo)
{
	sem_wait(philo->table->fork);
	if (print_msg(philo, FORK, get_time()))
		return (1);
	sem_wait(philo->table->fork);
	if (print_msg(philo, FORK, get_time()))
		return (1);
	if (print_msg(philo, EAT, get_time()))
		return (1);
	philo->last_meal = get_time();
	my_sleep(philo->table->time_to_eat, philo->table->is_philo_dead);
	sem_post(philo->table->fork);
	sem_post(philo->table->fork);
	philo->count_eat += 1;
	return (0);
}

void	*act_philo(void *philo)
{
	t_philos	*phi;
	pthread_t	tid;

	phi = (t_philos *)philo;
	pthread_create(&tid, NULL, chk_philo, phi);
	if (phi->philo_num % 2 == 0)
		my_sleep(1, phi->table->is_philo_dead);
	while (1)
	{
		if (eat(phi))
			break ;
		if (phi->count_eat == phi->table->times_need_to_eat)
			break ;
		if (print_msg(phi, SLEEP, get_time()))
			break ;
		my_sleep(phi->table->time_to_sleep, phi->table->is_philo_dead);
		if (print_msg(phi, THINK, get_time()))
			break ;
	}
	pthread_join(tid, NULL);
	return (0);
}
