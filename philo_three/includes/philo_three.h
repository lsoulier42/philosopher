/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:51:42 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/25 11:02:22 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <pthread.h>
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
	ALIVE
}					t_philo_state;

typedef struct		s_fork
{
	sem_t			*nb_forks_available;
	sem_t			*can_take_a_fork;
}					t_fork;

typedef struct		s_philo
{
	int				num;
	char			state;
	long			last_eat_date;
	long			last_sleep_date;
	int 			time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int 			nb_meal_max;
	long			start_ts;
	t_fork			*forks;
}					t_philo;

typedef struct 		s_process
{
	pid_t			process_id;
	int				*someone_has_died;
}					t_process;

typedef struct		s_data
{
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	long			start_ts;
	int 			someone_has_died;
	t_fork			forks;
	t_process		*process;
	t_philo			*philosophers;
}					t_data;

int					check_args(int argc, char **argv);
int					invalid_arg_num(char *arg);
int					invalid_arg_neg(char *arg);
int					invalid_arg_nb(void);

int					alloc_struct(t_data *philo_data);
int					init_struct(t_data *philo_data);
int					free_struct(t_data *philo_data);
int					init_data(t_data *philo_data, int argc, char **argv);
int					delete_data(t_data *philo_data);

long				get_timestamp(void);
int					ft_isnum(char *str);
int					ft_isdigit(int c);
int					ft_isspace(char c);
int					ft_atoi(const char *str);
void				print_state(long ts, int num, char state);

int					philo_loop(t_data *philo_data);

int					init_forks(t_data *philo_data);
int					delete_forks(t_data *philo_data);

int 				philo_routine(t_philo *philo);
void				routine_forks(t_philo *philo);
void				routine_sleep(t_philo *philo, long ts);
void				routine_eat(t_philo *philo, long ts);

int 				init_philosophers(t_data *philo_data);
int 				load_process(t_data *philo_data);
#endif
