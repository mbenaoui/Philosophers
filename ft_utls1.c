/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utls1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:05:36 by mbenaoui          #+#    #+#             */
/*   Updated: 2022/05/22 11:00:34 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	norm(t_simulation *philos, t_betw bet, int number, t_lanes *t)
{
	call_checker(philos, bet, number);
	pthread_mutex_lock(&philos->mutex);
	if (t->time != philos->test[number])
	{
		t->time = philos->test[number];
		t->eat += 1;
	}
	if (!c_ded(philos->philo_state, philos->info.philo_number)
		|| (philos->info.must_eat != -1 && t->eat >= philos->info.must_eat))
	{
		if (philos->info.must_eat != -1)
			philos->philo_state[number] = 0;
		pthread_mutex_unlock(&philos->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->mutex);
	usleep (50);
	return (0);
}

int	check_time(t_simulation *philos, int n, int len)
{
	struct timeval	c;
	long long		time;

	gettimeofday(&c, NULL);
	time = c.tv_sec * 1000 + (c.tv_usec / 1000) - philos->curr;
	if (len == 2)
	{
		if (time - philos->test[n] >= philos->info.time_to_eat)
			return (1);
		return (0);
	}
	if (len == 3)
	{
		if (time - philos->test[n] - philos->info.time_to_eat
			>= philos->info.time_to_sleep)
			return (1);
		return (0);
	}
	if (len == 4)
	{
		if (time - philos->test[n] > philos->info.time_to_die)
			return (1);
		return (0);
	}
	return (0);
}

int	check_condition(t_simulation *philos, int nb, t_betw bet, int len)
{
	if (len == 1)
	{
		if (philos->philo_state[nb] == 0 && philos->philo_state[bet.before] != 1
			&& philos->philo_state[bet.after] != 1 && check_test(philos, nb))
			return (1);
	}
	if (len == 2)
	{
		if (philos->philo_state[nb] == 1 && check_time(philos, nb, len))
			return (1);
	}
	if (len == 3)
	{
		if (check_time(philos, nb, len) && philos->philo_state[nb] == 2)
			return (1);
	}
	if (len == 4)
	{
		if (philos->philo_state[nb] != 1 && check_time(philos, nb, len))
			return (1);
	}
	return (0);
}

void	check_states1(t_simulation *p, t_betw bet, int nb, int len)
{
	struct timeval	t;

	if (len == 1)
	{
		if (check_condition(p, nb, bet, len)
			&& c_ded(p->philo_state, p->info.philo_number))
		{
			gettimeofday(&t, NULL);
			p->test[nb] = t.tv_sec * 1000 + (t.tv_usec / 1000) - p->curr;
			p->philo_state[nb] = 1;
			ft_printf(p, nb, 1, len);
		}
	}
	if (len == 2)
	{
		if (check_condition(p, nb, bet, len)
			&& c_ded(p->philo_state, p->info.philo_number))
		{
			gettimeofday(&t, NULL);
			len = t.tv_sec * 1000 + (t.tv_usec / 1000) - p->curr;
			p->philo_state[nb] = 2;
			ft_printf(p, nb, 2, len);
		}
	}
}

void	check_states(t_simulation *philos, t_betw bet, int nb, int len)
{
	struct timeval	t;

	check_states1(philos, bet, nb, len);
	if (len == 3)
	{
		if (check_condition(philos, nb, bet, len)
			&& c_ded(philos->philo_state, philos->info.philo_number))
		{
			gettimeofday(&t, NULL);
			len = t.tv_sec * 1000 + (t.tv_usec / 1000) - philos->curr;
			philos->philo_state[nb] = 0;
			ft_printf(philos, nb, 3, len);
		}
	}
	if (len == 4)
	{
		if (check_condition(philos, nb, bet, len)
			&& c_ded(philos->philo_state, philos->info.philo_number))
		{
			gettimeofday(&t, NULL);
			len = t.tv_sec * 1000 + (t.tv_usec / 1000) - philos->curr;
			philos->philo_state[nb] = 4;
			ft_printf(philos, nb, 4, len);
		}
	}
}
