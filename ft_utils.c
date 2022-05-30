/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:05:22 by mbenaoui          #+#    #+#             */
/*   Updated: 2022/05/21 17:04:19 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	call_checker(t_simulation *philos, t_betw bet, int number)
{
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 1);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 2);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 3);
	pthread_mutex_unlock(&philos->mutex);
	pthread_mutex_lock(&philos->mutex);
	check_states(philos, bet, number, 4);
	pthread_mutex_unlock(&philos->mutex);
}

void	*philo_1(t_simulation *philos, t_betw bet, int nb)
{
	while (bet.after == -1)
	{
		pthread_mutex_lock(&philos->mutex);
		check_states(philos, bet, nb, 4);
		pthread_mutex_unlock(&philos->mutex);
		pthread_mutex_lock(&philos->mutex);
		if (!c_ded(philos->philo_state, philos->info.philo_number))
		{
			pthread_mutex_unlock(&philos->mutex);
			break ;
		}
		pthread_mutex_unlock(&philos->mutex);
	}
	return (0);
}

void	*philo(void *p)
{
	t_simulation	*philos;
	t_betw			bet;
	int				nb;
	t_lanes			t;

	philos = p;
	nb = philos->num;
	philos->num = nb + 1;
	bet = ft_get_bet(philos, nb);
	t.time = 0;
	t.eat = 0;
	while (bet.before > -1)
	{
		if (norm(philos, bet, nb, &t))
			break ;
	}
	philo_1(philos, bet, nb);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo_info		info;
	t_simulation		philos;
	struct timeval		c;

	gettimeofday(&c, NULL);
	pthread_mutex_init(&philos.mutex, NULL);
	if (ac < 5 || ac > 6)
	{
		printf("%s", KRED);
		printf ("error\n");
		return (1);
	}
	ft_info(&info, ac, av);
	if (arg_checker(info) == 1)
		return (1);
	creat_philo_state(&philos, info);
	philos.curr = c.tv_sec * 1000 + (c.tv_usec / 1000);
	creat_pthread(&philos, info);
	free(philos.test);
	free(philos.philo_state);
	pthread_mutex_destroy(&philos.mutex);
	return (0);
}
