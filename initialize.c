/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:15:55 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/16 15:29:08 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_to_philos(t_data *data, t_philos *philo)
{
	philo->philos_amount = data->philos_amount;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->must_eat = data->must_eat;
}

void	initialize(t_data *data, t_philos *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	while (++i < data->philos_amount)
	{
		init_args_to_philos(data, &philos[i]);
		philos[i].start_time = data->start_time;
		philos[i].last_eaten = data->start_time;
		philos[i].nb = i + 1;
		philos[i].eating_now = 0;
		philos[i].times_eaten = 0;
		philos[i].stop = &data->stop;
		philos[i].eat_mutex = &data->eat_mutex;
		philos[i].die_mutex = &data->die_mutex;
		philos[i].write_mutex = &data->write_mutex;
		pthread_mutex_init(&forks[i], NULL);
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[data->philos_amount - 1];
		else
			philos[i].r_fork = &forks[i - 1];
	}
}
