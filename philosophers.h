/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:02:23 by mbenaoui          #+#    #+#             */
/*   Updated: 2022/05/21 19:05:59 by mbenaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define KRED  "\x1B[31m"
# define KYELLOW "\x1B[32m"
# define KGREEN   "\x1B[33m"
# define KBLUE  "\x1B[34m"
# define KMAGENTA  "\x1B[35m"
# define KCYAN  "\x1B[36m"
# define KWHITE  "\x1B[37m"
# define KNORMAL  "\x1B[0m"

typedef struct philo_info_s
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_philo_info;

typedef struct lanes
{
	long long	time;
	int			eat;
}	t_lanes;

typedef struct simulation_s
{
	int				*philo_state;
	pthread_mutex_t	mutex;
	t_philo_info	info;
	int				num;
	long long		curr;
	long long		*test;
}	t_simulation;

typedef struct bet_s
{
	int	before;
	int	after;
}	t_betw;

int		main(int ac, char **av);
int		ft_atoi(char *s);
void	call_checker(t_simulation *philos, t_betw bet, int number);
void	ft_info(t_philo_info *info, int ac, char *av[]);
void	creat_pthread(t_simulation *philos, t_philo_info info);
void	*philo(void *p);
void	check_states(t_simulation *philos, t_betw bet, int nb, int len);
void	ft_printf(t_simulation *philos, int nb, int len, long long time);
int		check_time(t_simulation *philos, int n, int len);
void	check_states(t_simulation *philos, t_betw bet, int nb, int len);
int		norm(t_simulation *philos, t_betw bet, int number, t_lanes *t);
int		c_ded(int *str, int nb);
int		check_condition(t_simulation *philos, int nb, t_betw bet, int len);
t_betw	ft_get_bet(t_simulation *philos, int nb);
int		check_tab_test(t_simulation *philos, int nb);
void	creat_philo_state(t_simulation *philos, t_philo_info info);
int		check_test(t_simulation *philos, int num);
int		arg_checker(t_philo_info info);
#endif
