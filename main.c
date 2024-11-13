/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:44 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/16 20:37:01 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philos *philo, char *str, int nb)
{
	size_t	time;

	pthread_mutex_lock(philo->write_mutex);
	time = get_time() - philo->start_time;
	if (!check_stop(philo))
		printf("%zu %d %s\n", time, nb, str);
	pthread_mutex_unlock(philo->write_mutex);
}

void	destroy_free_all(t_data *data, t_philos *philos,
			pthread_mutex_t *forks, char *str)
{
	int	i;

	i = -1;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	while (++i < data->philos_amount)
		pthread_mutex_destroy(&forks[i]);
	free(philos);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philos		*philos;
	pthread_mutex_t	*forks;

	if (check_init_args(&data, argc, argv))
		return (1);
	philos = malloc(sizeof(t_philos) * data.philos_amount);
	if (!philos)
		return (printf("Allocation of philos failed!"), 1);
	forks = malloc(sizeof(pthread_mutex_t) * data.philos_amount);
	if (!forks)
	{
		free(philos);
		return (printf("Allocation of forks failed!"), 1);
	}
	data.philos = philos;
	initialize(&data, philos, forks);
	run_sequences(&data, philos, forks);
	destroy_free_all(&data, philos, forks, NULL);
	return (0);
}
