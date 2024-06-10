/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:14:23 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/18 09:36:04 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	*deus_ex_machina(void *data_ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *) data_ptr;
	while (!all_philos_are_playing(data))
		;
	while (data->dead == 0)
	{
		i = -1;
		while (++i < data->nb_philos && data->dead == 0)
		{
			if (philo_died(&data->philos[i]))
			{
				switch_to_died(data);
				message(DIED, &data->philos[i]);
			}
			if (data->nb_meals > 0 && data->finished == data->nb_philos)
				switch_to_died(data);
		}
	}
	return ((void *)0);
}

static void	*destiny(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (!philo->data->all_threads_ready)
		;
	philo->last_eat = get_time(MILLISECOND);
	if (pthread_mutex_lock(&philo->data->lock) == 0)
		philo->data->nb_threads_run++;
	pthread_mutex_unlock(&philo->data->lock);
	desynchronize_philos(philo);
	while (philo->data->dead == 0)
	{
		to_eat(philo);
		message(SLEEPING, philo);
		ft_usleep(philo->data->time_sleep);
		to_thinking(philo, 0);
	}
	return ((void *)0);
}

static void	*lonely_destiny(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (!philo->data->all_threads_ready)
		;
	philo->last_eat = get_time(MILLISECOND);
	if (pthread_mutex_lock(&philo->data->lock) == 0)
		philo->data->nb_threads_run++;
	pthread_mutex_unlock(&philo->data->lock);
	message(TAKE_FORKS, philo);
	while (philo->data->dead == 0)
		ft_usleep(200);
	return (0);
}

int	init_lonely_philo(t_data *data)
{
	data->time_start = get_time(MILLISECOND);
	if (pthread_create(&data->philos[0].thread_id,
			NULL, &lonely_destiny, &data->philos[0]))
		return (error_manager(data, ERR_CR_THR, 1));
	if (pthread_create(&data->monitor, NULL, &deus_ex_machina, data))
		return (error_manager(data, ERR_CR_THR, 1));
	data->all_threads_ready = 1;
	if (pthread_join(data->philos[0].thread_id, NULL))
		return (error_manager(data, ERR_JOIN_THR, 1));
	data->dead = 1;
	if (pthread_join(data->monitor, NULL))
		return (error_manager(data, ERR_JOIN_THR, 1));
	return (0);
}

int	init_routine(t_data *data)
{
	int	i;

	i = -1;
	data->time_start = get_time(MILLISECOND);
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread_id,
				NULL, &destiny, &data->philos[i]))
			return (error_manager(data, ERR_CR_THR, 1));
	}
	if (pthread_create(&data->monitor, NULL, &deus_ex_machina, data))
		return (error_manager(data, ERR_CR_THR, 1));
	data->all_threads_ready = 1;
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (error_manager(data, ERR_JOIN_THR, 1));
	}
	data->dead = 1;
	if (pthread_join(data->monitor, NULL))
		return (error_manager(data, ERR_JOIN_THR, 1));
	return (0);
}
