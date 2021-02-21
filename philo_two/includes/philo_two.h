/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:05:38 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 00:05:41 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# define MIN_NB_ARGS 5
# define MAX_NB_ARGS 6

typedef enum		e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	TOTAL_STATES
}					t_philo_state;

typedef enum		e_thread_errors
{
	CREATE_THREAD_ERROR,
	SEM_OPEN_ERROR,
	SEM_CLOSE_ERROR,
	SEM_POST_ERROR,
	TOTAL_THREAD_ERRORS
}					t_thread_errors;

typedef struct		s_philo
{
	int				num;
	int				state;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	long			last_eat_date;
	long			start_ts;
	int				nb_meal;
	int				is_finished;
	sem_t			*forks;
	sem_t			*output;
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
	sem_t			*forks;
	sem_t			*output;
	t_philo			*philosophers;
}					t_data;

int					init_data(t_data *philo_data, int argc, char **argv);
int					delete_data(t_data *philo_data);
int					alloc_struct(t_data *philo_data);
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

void				*thread_error(int code);

void				*philo_routine(void *philo_data_void);

void				routine_eat(t_philo *philo);
void				*routine_death(void *philo_void);

int					init_semaphores(t_data *philo_data);
int					delete_semaphores(t_data *philo_data);
void				unlink_semaphores(void);

long				get_timestamp(long start_ts);
void				ft_usleep(int duration);
void				print_state(int is_finished, char *ts_str,
						char *num_str, char *state);
char				*ft_itoa(int n);

#endif
