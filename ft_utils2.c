/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:27:07 by mbenaoui          #+#    #+#             */
/*   Updated: 2022/05/22 10:41:19 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_printf(t_simulation *philos, int nb, int len, long long time)
{
	if (len == 1)
	{
		printf("%lld %d >> has taken fork\n", philos->test[nb], nb + 1);
		printf("%lld %d >> has taken fork\n", philos->test[nb], nb + 1);
		printf("%lld %d >> is eating\n", philos->test[nb], nb + 1);
	}
	if (len == 2)
	{
		printf("%lld %d >> is selping\n", time, nb + 1);
	}
	if (len == 3)
		printf("%lld %d >> is thinking\n", time, nb + 1);
	if (len == 4)
	{
		printf("%s", KGREEN);
		printf("%lld %d ------->> is died\n", time, nb + 1);
	}
}

int	c_ded(int *str, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (str[i] == 4)
			return (0);
		i++;
	}
	return (1);
}

int	check_test(t_simulation *philos, int num)
{
	int	i;

	i = 0;
	while (i < philos->info.philo_number)
	{
		if (philos->test[num] > philos->test[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int		i;
	int		signe;
	int		num;

	i = 0;
	signe = 1;
	num = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + s[i] - '0';
		i++;
	}
	if (s[i])
		return (0);
	return (num * signe);
}

void	ft_info(t_philo_info *info, int ac, char *av[])
{
	info->philo_number = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = -1;
}
