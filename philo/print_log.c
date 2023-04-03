/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:42:49 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/27 23:48:51 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	lock(t_philo *philo, size_t *time, int *dead_or_alive, int *status)
{
	pthread_mutex_lock(&(philo->info->log_lock));
	pthread_mutex_lock(&(philo->info->time_lock));
	*time = philo->info->log;
	pthread_mutex_unlock(&(philo->info->time_lock));
	pthread_mutex_lock(&(philo->info->dead_or_alive_lock));
	*dead_or_alive = philo->dead_or_alive;
	pthread_mutex_unlock(&(philo->info->dead_or_alive_lock));
	pthread_mutex_lock(&(philo->info->status_lock));
	*status = philo->status;
	pthread_mutex_unlock(&(philo->info->status_lock));
}

void	print_log(t_philo *philo, int option)
{
	size_t	time;
	int		dead_or_alive;
	int		status;

	lock(philo, &time, &dead_or_alive, &status);
	if (dead_or_alive == LIVE && option == DIED)
		kill_philo(philo);
	else if (status == THINKING && option == FORK
		&& dead_or_alive == LIVE)
		printf("%zu %d has taken a fork\n",
			time - philo->info->start, philo->number);
	else if (status == THINKING && dead_or_alive == LIVE)
		printf("%zu %d is thinking\n", time - philo->info->start, philo->number);
	else if (status == EATING && dead_or_alive == LIVE)
		printf("%zu %d is eating\n", time - philo->info->start, philo->number);
	else if (status == SLEEPING && dead_or_alive == LIVE)
		printf("%zu %d is sleeping\n", time - philo->info->start, philo->number);
	pthread_mutex_unlock(&(philo->info->log_lock));
}
