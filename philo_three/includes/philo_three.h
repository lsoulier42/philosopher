/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:00:44 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/18 12:00:47 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>
# define UNLIMITED_MEAL -1
# define MIN_NB_ARGS 5
# define MAX_NB_ARGS 6

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
	SEM_OPEN_ERROR,
	SEM_CLOSE_ERROR,
	SEM_POST_ERROR,
	SEM_WAIT_ERROR,
	DETACH_THREAD_ERROR,
	FORK_ERROR,
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
	int				*nb_finished;
	int				nb_philo;
	sem_t			*forks;
	sem_t			*output;
	sem_t			*is_dead;
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
	sem_t			*is_dead;
	pid_t			*philosophers_processes;
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
int					load_processes(t_data *philo_data);
int					delete_processes(t_data *philo_data);
void				*thread_error(int code);

void				*philo_routine(void *philo_data_void);
void				philo_loop(t_philo *philo, int *nb_meals);
void				routine_eat(t_philo *philo);
void				*routine_death(void *philo_void);

int					init_semaphores(t_data *philo_data);
int					delete_semaphores(t_data *philo_data);
void				unlink_semaphores(void);

long				get_timestamp(long start_ts);
void				print_state(t_philo *philo, int is_dead);

#endif
