/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:56:44 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/12 09:53:37 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_exit(t_data *data)
{
	ft_clear_mutex(data);
	ft_clear_alloc(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (print_error(ERR_ARGS));
	if (init(&data, argv))
		return (1);
	if (data.nb_philos == 1)
		init_lonely_philo(&data);
	else if (init_routine(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
