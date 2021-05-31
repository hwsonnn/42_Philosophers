/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hson <hson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:08:46 by hson              #+#    #+#             */
/*   Updated: 2021/05/31 15:10:21 by hson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void			my_sleep(int ms, int is_dead)
{
	unsigned long	start_time;

	start_time = get_time();
	while (start_time + ms > get_time())
	{
		if (is_dead)
			break ;
		usleep(100);
	}
}

int				ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		num;
	int		digit_count;

	i = 0;
	sign = 1;
	num = 0;
	digit_count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '+' || str[i] == '-')
		sign *= str[i++] == '+' ? 1 : -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + str[i] - '0';
		++i;
		++digit_count;
		if (digit_count == 20)
			return (sign == -1) ? 0 : -1;
	}
	return (num * sign);
}
