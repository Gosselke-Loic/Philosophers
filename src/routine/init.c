/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:04:51 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/13 13:03:58 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	init_forks(t_data *data, int i)
{
	data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
	data->philos[i].left_fork = &data->forks[i];
	if (data->philos[i].id % 2 == 0)
	{
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nb_philos];
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;
	int	error;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].full = 0;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_count = 0;
		error = pthread_mutex_init(&data->philos[i].lock, NULL);
		if (error)
			return (error_manager(data, ERR_MUTEX, 1));
		init_forks(data, i);
	}
	return (0);
}

static int	alloc_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (error_manager(data, ERR_MALLOC, 1));
	data->philos = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philos)
		return (error_manager(data, ERR_MALLOC, 1));
	if (pthread_mutex_init(&data->write, NULL))
		return (error_manager(data, ERR_MUTEX, 1));
	if (pthread_mutex_init(&data->lock, NULL))
		return (error_manager(data, ERR_MUTEX, 1));
	return (0);
}

static int	init_data(t_data *data, char **argv)
{
	data->dead = 0;
	data->finished = 0;
	data->nb_threads_run = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->time_eat = ft_atoi(argv[3]) * 1e3;
	data->time_death = ft_atoi(argv[2]) * 1e3;
	data->time_sleep = ft_atoi(argv[4]) * 1e3;
	if (data->nb_philos <= 0 || data->time_death < 2e4
		|| data->time_eat < 2e4 || data->time_sleep < 2e4)
		return (error_manager(data, ERR_FORMAT, 0));
	if (argv[5])
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	if (argv[5] && data->nb_meals <= 0)
		return (error_manager(data, ERR_FORMAT, 0));
	return (0);
}

int	init(t_data *data, char **argv)
{
	int	i;

	data->forks = NULL;
	data->philos = NULL;
	if (!only_numeric(argv))
		return (error_manager(data, ERR_FORMAT, 0));
	if (init_data(data, argv))
		return (1);
	if (alloc_data(data))
		return (1);
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error_manager(data, ERR_MUTEX, 1));
	}
	if (init_philos(data))
		return (1);
	return (0);
}
