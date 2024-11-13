/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:18:14 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/16 17:01:53 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philos
{
	pthread_t		thread;
	int				nb;
	int				eating_now;
	int				times_eaten;
	int				must_eat;
	int				philos_amount;
	int				*stop;
	size_t			start_time;
	size_t			last_eaten;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*write_mutex;
}					t_philos;

typedef struct s_data
{
	int				philos_amount;
	int				must_eat;
	int				stop;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	write_mutex;
	t_philos		*philos;
}					t_data;

// Main //

void	print_action(t_philos *philo, char *str, int nb);
void	destroy_free_all(t_data *data, t_philos *philos,
			pthread_mutex_t *forks, char *str);
int		main(int argc, char **argv);

// Utils //

int		ft_str_isdigit(char *str);
int		check_init_args(t_data *data, int argc, char **argv);
size_t	get_time(void);
void	ft_usleep(size_t m_sec);
int		ft_atoi(const char *str);

// Initialize //

void	init_args_to_philos(t_data *data, t_philos *philo);
void	initialize(t_data *data, t_philos *philos, pthread_mutex_t *forks);

// Sequences //

void	philo_eat(t_philos *philo);
void	philo_sleep(t_philos *philo);
void	philo_think(t_philos *philo);
void	*philo_sequence(void *ptr);
void	run_sequences(t_data *data, t_philos *philos, pthread_mutex_t *forks);

// Control //

int		check_stop(t_philos *philo);
int		starve_check(t_philos *philos);
int		must_eat_check(t_philos *philos);
void	*control(void *ptr);

#endif