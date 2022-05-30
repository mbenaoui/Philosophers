/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:19:31 by mbenaoui          #+#    #+#             */
/*   Updated: 2022/05/21 17:20:57 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arg_checker(t_philo_info info)
{
	if (info.philo_number < 1)
	{
		printf("%s", KRED);
		printf ("the number of philosophers is less than 1 or not digit\n");
		return (1);
	}
	if (info.time_to_die < 60)
	{
		printf("%s", KCYAN);
		printf ("the time_to_die is less than 60 or not digit\n");
		return (1);
	}
	if (info.time_to_eat < 60)
	{
		printf("%s", KBLUE);
		printf ("the time_to_eat is less than 60 or not digit\n");
		return (1);
	}
	return (0);
}

int	check_tab_test(t_simulation *philos, int nb)
{
	int	i;

	i = 0;
	while (i < philos->info.philo_number)
	{
		if (philos->test[i] < philos->test[nb])
			return (0);
		i++;
	}
	return (1);
}

t_betw	ft_get_bet(t_simulation *philos, int nb)
{
	t_betw	bet;

	if (nb == 0)
		bet.before = philos->info.philo_number - 1;
	else
		bet.before = nb - 1;
	if (nb == philos->info.philo_number - 1)
		bet.after = 0;
	else
		bet.after = nb + 1;
	if (philos->info.philo_number == 1)
	{
		bet.before = -1;
		bet.after = -1;
	}
	return (bet);
}

void	creat_pthread(t_simulation *philos, t_philo_info info)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * info.philo_number);
	philos->num = 0;
	while (i < info.philo_number)
	{
		pthread_create(&th[i], NULL, &philo, philos);
		i++;
	}
	i = 0;
	while (i < info.philo_number)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

void	creat_philo_state(t_simulation *philos, t_philo_info info)
{
	int	i;

	i = 0;
	philos->info = info;
	philos->num = 0;
	philos->philo_state = malloc (sizeof(int) * info.philo_number);
	philos->test = malloc (sizeof(long long) * info.philo_number);
	while (i < info.philo_number)
	{
		philos->philo_state[i] = 0;
		philos->test[i] = 0;
		i++;
	}
}
