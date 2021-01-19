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

typedef enum		e_philo_state
{
	EAT,
	SLEEP,
	THINK,
	NONE
}					t_philo_state;

typedef struct		s_philo
{
	pthread_t	tid;
	int			num;
	char		state;
	char		alive;
	char		nb_forks_taken;
	long long	last_eat_date;
	long long	last_sleep_date;
}					t_philo;

typedef struct		s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal_max;
	int 			nb_forks;
	pthread_mutex_t	*forks;
	int				nb_meal;
	int 			someone_died;
	int 			current_philo;
	t_philo	*philosophers;
}					t_data;

int					init_data(t_data *philo_data, int argc, char **argv);
int					invalid_arg_nb(void);
int					invalid_arg_num(char *arg);
int					invalid_arg_neg(char *arg);
int					ft_atoi(const char *str);
int					ft_isspace(char c);
int					check_arg(int argc, char **argv);
int					ft_isnum(char *str);
int					ft_isdigit(int c);
int					philo_loop(t_data *philo_data);
int					philo_loop_error(t_data philo_data);
int					init_threads(t_data *philo_data, t_philo *philosophers);
void				*philo_routine(void *philo_data_void);

#endif