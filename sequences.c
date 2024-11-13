/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequences.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:16:56 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/17 15:13:39 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, "has taken a fork", philo->nb);
	if (philo->philos_amount == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork", philo->nb);
	philo->eating_now = 1;
	print_action(philo, "is eating", philo->nb);
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_eaten = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
	philo->eating_now = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philos *philo)
{
	print_action(philo, "is sleeping", philo->nb);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philos *philo)
{
	print_action(philo, "is thinking", philo->nb);
}

void	*philo_sequence(void *ptr)
{
	t_philos	*philo;

	philo = (t_philos *)ptr;
	if (philo->nb % 2 == 0)
		ft_usleep(5);
	while (!check_stop(philo))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (ptr);
}

void	run_sequences(t_data *data, t_philos *philos, pthread_mutex_t *forks)
{
	pthread_t	control_thread;
	int			i;

	i = 0;
	if (pthread_create(&control_thread, NULL, &control, data->philos) != 0)
		destroy_free_all(data, philos, forks, "Pthread_create error!");
	while (i < data->philos_amount)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_sequence,
				&data->philos[i]) != 0)
			destroy_free_all(data, philos, forks, "Pthread_create error!");
		i++;
	}
	i = 0;
	if (pthread_join(control_thread, NULL) != 0)
		destroy_free_all(data, philos, forks, "Pthread_join error!");
	while (i < data->philos_amount)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_free_all(data, philos, forks, "Pthread_join error!");
		i++;
	}
}
