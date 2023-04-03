/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:45:52 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/27 23:48:00 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR 1
# define SUCCESS 0

# define NOTHING -1
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define FORK 3
# define LIVE 4
# define DIED 5
# define ENOUGH 6

typedef struct s_info	t_info;

typedef struct s_philo
{
	int				number;
	int				dead_or_alive;
	int				status;
	int				left;
	int				right;
	t_info			*info;
	pthread_t		life;
	pthread_t		monitor;
	int				meal_count;
	size_t			last_meal_time;
}t_philo;

typedef struct s_info{
	int				philo_num;
	size_t			die;
	size_t			eat;
	size_t			sleep;
	size_t			start;
	size_t			log;
	int				must_eat_flag;
	int				must_eat;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	dead_or_alive_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	log_lock;
}t_info;

// main.c
void	print_log(t_philo *philo, int option);
void	kill_philo(t_philo *philo);

//ft_atoi.c
int		ft_atoi(const char *str);

// info_init.c
int		info_init(t_info *info, int argc, char **argv);

// monitoring.c
void	monitoring(t_philo *philo);

// simulation.c
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// utils.c
size_t	get_timestamp(void);
void	pass_time(size_t time);
int		check_argv(int argc, char **argv);

#endif