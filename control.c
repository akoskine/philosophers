/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:17:45 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/16 20:19:49 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_philos *philo)
{
	pthread_mutex_lock(philo->die_mutex);
	if (*philo->stop == 1)
		return (pthread_mutex_unlock(philo->die_mutex), 1);
	pthread_mutex_unlock(philo->die_mutex);
	return (0);
}

int	starve_check(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philos_amount)
	{
		pthread_mutex_lock(philos[i].eat_mutex);
		if (get_time() - philos[i].last_eaten >= philos[0].time_to_die
			&& !philos[i].eating_now)
		{
			pthread_mutex_unlock(philos[i].eat_mutex);
			print_action(&philos[i], "died", philos[i].nb);
			pthread_mutex_lock(philos[0].die_mutex);
			*philos->stop = 1;
			pthread_mutex_unlock(philos[0].die_mutex);
			return (1);
		}
		else
			pthread_mutex_unlock(philos[i].eat_mutex);
		i++;
	}
	return (0);
}

int	must_eat_check(t_philos *philos)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (philos[0].must_eat < 0)
		return (0);
	while (i < philos[0].philos_amount)
	{
		pthread_mutex_lock(philos[i].eat_mutex);
		if (philos[i].times_eaten >= philos[i].must_eat)
			flag++;
		pthread_mutex_unlock(philos[i].eat_mutex);
		i++;
	}
	if (flag == philos[0].philos_amount)
	{
		pthread_mutex_lock(philos[0].die_mutex);
		*philos->stop = 1;
		pthread_mutex_unlock(philos[0].die_mutex);
		return (1);
	}
	return (0);
}

void	*control(void *ptr)
{
	t_philos	*philos;

	philos = (t_philos *)ptr;
	while (1)
		if (starve_check(philos) || must_eat_check(philos))
			break ;
	return (ptr);
}
