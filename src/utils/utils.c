/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:10:37 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/13 10:46:47 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	only_numeric(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			while (argv[i][j] == '+')
				j++;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
		}
	}
	return (1);
}

void	ft_usleep(long time)
{
	long	rem;
	long	start;
	long	elapsed;

	start = get_time(MICROSECOND);
	while ((get_time(MICROSECOND) - start) < time)
	{
		elapsed = get_time(MICROSECOND) - start;
		rem = time - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while ((get_time(MICROSECOND) - start) < time)
				;
	}
}

long	get_time(int code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (error_manager(NULL, ERR_GETTIME, 1));
	if (MILLISECOND == code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int     i;
	long    res;

	if (!str)
		return (0);
	i = -1;
	res = 0;
	while (str[++i])
		res = (res * 10) + (str[i] - '0');
	if (res > INT_MAX)
		return (-1);
	return ((int)res);
}
