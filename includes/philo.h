/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:56:33 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/18 09:34:07 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/* DEFINE */
# define RESET "\033[0m"
# define RED "\033[1;31m"
# define BLUE "\033[0;36m"
# define BOLD "\033[1;37m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"

# define STATES_0 "died"
# define STATES_1 "is eating"
# define STATES_3 "is thinking"
# define STATES_2 "is sleeping"
# define STATES_4 "has taken a fork"

# define ERR_MALLOC "MALLOC"
# define ERR_MUTEX "MUTEX INIT"
# define ERR_GETTIME "GETTIMEOFDAY ERROR"
# define ERR_CR_THR "THREAD CAN'T BE CREATED"
# define ERR_ARGS "WRONG NUMBER OF ARGUMENTS"
# define ERR_JOIN_THR "THREAD CAN'T BE JOINED"
# define ERR_FORMAT "WRONG FORMAT OF SOME OF THE ARGUMENTS"

/* ENUM */
enum e_states
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORKS
};

enum e_times
{
	MILLISECOND,
	MICROSECOND
};

/* STRUCTURES */

struct	s_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	lock;
	int				full;
	struct s_data	*data;
	long			last_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals_count;
}				t_philo;

typedef struct s_data
{
	int				dead;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
	int				finished;
	long			nb_meals;
	long			time_eat;
	long			nb_philos;
	long			time_death;
	long			time_sleep;
	long			time_start;
	long			nb_threads_run;
	int				all_threads_ready;
}				t_data;

/* PROTOTYPES */

void		ft_exit(t_data *data);

/* UTILS */
void		ft_usleep(long time);
long		get_time(int time_code);
long		ft_atoi(const char *str);
int			only_numeric(char **argv);
int			ft_strlen(const char *str);

/* UTILS 2 */
int			philo_died(t_philo *philo);
void		switch_to_died(t_data *data);
int			all_philos_are_playing(t_data *data);
void		desynchronize_philos(t_philo *philo);

/* ROUTINE */
int			init_routine(t_data *data);
int			init_lonely_philo(t_data *data);

/* INIT */
int			init(t_data *data, char **argv);

/* ACTIONS */
void		to_eat(t_philo *philo);

void		message(int state, t_philo *philo);
void		to_thinking(t_philo *philo, int synchro);

/* ERRORS */
void		ft_clear_alloc(t_data *data);
void		ft_clear_mutex(t_data *data);
int			print_error(const char *error);
int			error_manager(t_data *data, const char *error, int mutex);

#endif