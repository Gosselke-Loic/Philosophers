/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:48:10 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/14 15:30:17 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	switch_to_died(t_data *data)
{
	if (pthread_mutex_lock(&data->lock) == 0)
		data->dead = 1;
	pthread_mutex_unlock(&data->lock);
}

int	all_philos_are_playing(t_data *data)
{
	int	boolean;

	boolean = 0;
	if (pthread_mutex_lock(&data->lock) == 0)
	{
		if (data->nb_threads_run == data->nb_philos)
			boolean = 1;
	}
	pthread_mutex_unlock(&data->lock);
	return (boolean);
}

void	desynchronize_philos(t_philo *philo)
{
	if (philo->data->nb_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4);
	}
	else
	{
		if (philo->id % 2)
			to_thinking(philo, 1);
	}
}

int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_death;

	if (philo->full == 1)
		return (0);
	elapsed = get_time(MILLISECOND) - philo->last_eat;
	time_death = philo->data->time_death / 1e3;
	if (elapsed > time_death)
		return (1);
	return (0);
}
