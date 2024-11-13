/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:31 by akoskine          #+#    #+#             */
/*   Updated: 2023/11/17 15:41:25 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_init_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments!\n"), 1);
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| ft_str_isdigit(argv[1]))
		return (printf("Wrong amount of philosophers!\n"), 1);
	if (ft_atoi(argv[2]) <= 0 || ft_str_isdigit(argv[2]))
		return (printf("Incorrect value of time to die\n"), 1);
	if (ft_atoi(argv[3]) <= 0 || ft_str_isdigit(argv[3]))
		return (printf("Incorrect value of time to eat\n"), 1);
	if (ft_atoi(argv[4]) <= 0 || ft_str_isdigit(argv[4]))
		return (printf("Incorrect value of time to sleep\n"), 1);
	if ((argv[5]) && (ft_atoi(argv[5]) < 0 || argv[5][0] == '\0'
		|| ft_str_isdigit(argv[5])))
		return (printf("Incorrect value of times philosophers to eat\n"), 1);
	data->philos_amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->stop = 0;
	data->start_time = get_time();
	return (0);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error in gettimeofday -function!\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t m_sec)
{
	size_t	current;

	current = get_time();
	while ((get_time() - current) < m_sec)
		usleep(500);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		b *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + *str - '0';
		str++;
	}
	return (a * b);
}
