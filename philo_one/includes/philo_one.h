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
# define NOT_EATEN_YET -1
# define NOT_SLEPT_YET -1

typedef enum		e_fork_id
{
	LEFT,
	RIGHT
}					t_fork_id;

typedef enum		e_philo_state
{
	NONE,
	EAT,
	SLEEP,
	THINK,
	HAS_TAKEN_FORK,
	DEAD
}					t_philo_state;

typedef struct		s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	int 			*someone_died_ptr;
	int 			*meal_taken_ptr;
	int				num;
	char			state;
	char			nb_forks_taken;
	long long		last_eat_date;
	long long		last_sleep_date;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
}					t_philo;

typedef struct		s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int 			someone_died;
	int 			nb_meal_taken;
	pthread_mutex_t	*forks;
	pthread_t 		*threads;
	t_philo 		*philosophers;
}					t_data;

int					init_data(t_data *philo_data, int argc, char **argv);
int					delete_data(t_data *philo_data);
int 				alloc_struct(t_data *philo_data);
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

int					init_forks(t_data *philo_data);
int 				delete_forks(t_data *philo_data);
void				take_forks(t_philo *philo);
void				leave_forks(t_philo *philo);

long long			get_current_timestamp(void);
void				print_state(int num, char state);

#endif