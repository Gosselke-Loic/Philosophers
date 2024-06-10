/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:14:43 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/18 09:36:06 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	message(int state, t_philo *philo)
{
	long	elapsed;

	if (philo->full == 1)
		return ;
	elapsed = get_time(MILLISECOND) - philo->data->time_start;
	if (pthread_mutex_lock(&philo->data->write) == 0)
	{
		if (state == DIED && philo->data->dead == 1)
			printf(BOLD"%ld"RED" %d %s\n"RESET, elapsed, philo->id, STATES_0);
		if (philo->data->dead == 0)
		{
			if (state == EATING)
				printf(BOLD"%ld"GREEN" %d %s\n"RESET,
					elapsed, philo->id, STATES_1);
			if (state == SLEEPING)
				printf(BOLD"%ld"BLUE" %d %s\n"RESET,
					elapsed, philo->id, STATES_2);
			if (state == THINKING)
				printf(BOLD"%ld"PURPLE" %d %s\n"RESET,
					elapsed, philo->id, STATES_3);
			if (state == TAKE_FORKS)
				printf(BOLD"%ld"RESET" %d %s\n", elapsed, philo->id, STATES_4);
		}
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	to_thinking(t_philo *philo, int synchro)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!synchro)
		message(THINKING, philo);
	if (philo->data->nb_philos % 2 == 0)
		return ;
	time_eat = philo->data->time_eat;
	time_sleep = philo->data->time_sleep;
	time_think = (time_eat * 2) - time_sleep;
	if (time_think < 0)
		time_think = 0;
	ft_usleep(time_think * 0.42);
}

void	to_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) == 0)
		message(TAKE_FORKS, philo);
	if (pthread_mutex_lock(philo->left_fork) == 0)
		message(TAKE_FORKS, philo);
	if (pthread_mutex_lock(&philo->lock) == 0)
		philo->last_eat = get_time(MILLISECOND);
	pthread_mutex_unlock(&philo->lock);
	philo->meals_count++;
	message(EATING, philo);
	ft_usleep(philo->data->time_eat);
	if (philo->data->nb_meals > 0
		&& philo->meals_count == philo->data->nb_meals)
	{
		if (pthread_mutex_lock(&philo->lock) == 0)
			philo->full = 1;
		pthread_mutex_unlock(&philo->lock);
		if (pthread_mutex_lock(&philo->data->lock) == 0)
			philo->data->finished++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
