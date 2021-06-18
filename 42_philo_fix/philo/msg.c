/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:00:05 by hson              #+#    #+#             */
/*   Updated: 2021/06/18 15:45:25 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		print_msg(t_philos *philo, int status, unsigned long curr_time)
{
	// pthread_mutex_lock(&(philo->table->msg));
	if (philo->table->is_philo_dead)
	{
		// pthread_mutex_unlock(&(philo->table->msg));
		return (1);
	}
	if (status == FORK)
		printf("%lu %d has taken a fork\n",
				curr_time - philo->table->start_time, philo->philo_num + 1);
	else if (status == EAT)
		printf("%lu %d is eating\n",
				curr_time - philo->table->start_time, philo->philo_num + 1);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n",
				curr_time - philo->table->start_time, philo->philo_num + 1);
	else if (status == THINK)
		printf("%lu %d is thinking\n",
				curr_time - philo->table->start_time, philo->philo_num + 1);
	else if (status == DIED)
	{
		philo->table->is_philo_dead = 1;
		printf("%lu %d is died\n",
				curr_time - philo->table->start_time, philo->philo_num + 1);
	}
	// pthread_mutex_unlock(&(philo->table->msg));
	return (0);

}

int		ft_error(char *s)
{
	printf("%s", s);
	return (-1);
}
