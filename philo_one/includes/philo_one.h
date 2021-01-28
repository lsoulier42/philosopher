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
# define UNLIMITED_MEAL -1
# define MIN_NB_ARGS 5
# define MAX_NB_ARGS 6

typedef enum		e_fork_status
{
	UNLOCKED,
	LOCKED
}					t_fork_status;

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
	DEAD
}					t_philo_state;

typedef struct		s_fork
{
	pthread_mutex_t mutex_id;
	char			state;
}					t_fork;

typedef struct		s_philo
{
	int				num;
	char			state;
	int				last_eat_date;
	int				last_sleep_date;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int				start_ts;
	t_fork			*forks[2];
}					t_philo;

typedef struct		s_data
{
	int				nb_philo;
	int 			nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int				start_ts;
	t_fork			*forks;
	pthread_t		*threads;
	t_philo			*philosophers;
}					t_data;

extern int			g_someone_has_died;

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

int					philo_loop(t_data *philo_data);

void				init_philosophers(t_data *philo_data);
int					load_threads(t_data *philo_data);
int					delete_philosophers(t_data *philo_data);

void				*philo_routine(void *philo_data_void);
void				routine_eat(t_philo *philo, int ts);
void				routine_sleep(t_philo *philo, int ts);
void				routine_forks(t_philo *philo);

int					init_forks(t_data *philo_data);
int					delete_forks(t_data *philo_data);
int					leave_forks(t_philo *philo);
int					take_a_fork(t_philo *philo, int side_id);

long				get_timestamp(void);
void				print_state(int ts, int num, char state);

#endif
