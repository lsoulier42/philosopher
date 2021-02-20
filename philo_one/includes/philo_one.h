/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:13:44 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/19 09:13:49 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# define MIN_NB_ARGS 5
# define MAX_NB_ARGS 6

typedef enum		e_fork_side
{
	LEFT,
	RIGHT
}					t_fork_side;

typedef enum		e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	HAS_FORKS,
	DEAD,
	TOTAL_STATES
}					t_philo_state;

typedef enum		e_thread_errors
{
	CREATE_THREAD_ERROR,
	MUTEX_INIT_ERROR,
	TOTAL_THREAD_ERRORS
}					t_thread_errors;

typedef struct		s_philo
{
	int				num;
	int				state;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int				nb_meal;
	int				last_eat_date;
	long			start_ts;
	int				is_finished;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*output;
}					t_philo;

typedef struct		s_data
{
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int				nb_finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_t		*philosophers_threads;
	t_philo			*philosophers;
}					t_data;

int					init_data(t_data *philo_data, int argc, char **argv);
int					delete_data(t_data *philo_data);
int					alloc_struct(t_data *philo_data);
int					free_struct(t_data *philo_data);
int					init_struct(t_data *philo_data);

int					check_args(int argc, char **argv);
int					invalid_arg_nb(void);
int					invalid_arg_num(char *arg);
int					invalid_arg_neg(char *arg);
int					ft_atoi(const char *str);
int					ft_isspace(char c);
int					ft_isnum(char *str);
int					ft_isdigit(int c);

int					init_philosophers(t_data *philo_data);
int					load_threads(t_data *philo_data);
int					delete_threads(t_data *philo_data);
void				*thread_error(int code);

void				*philo_routine(void *philo_data_void);
void				routine_eat(t_philo *philo);

int					init_mutexes(t_data *philo_data);
int					delete_mutexes(t_data *philo_data);

long				get_timestamp(long start_ts);
void				ft_usleep(int duration);

void				print_state(t_philo *philo, int is_dead);
void				monitor_loop(t_data *philo_data, long start_ts);

#endif
