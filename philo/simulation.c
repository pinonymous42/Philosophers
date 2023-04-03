/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:52:17 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/27 12:07:29 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->fork[philo->left]));
	print_log(philo, FORK);
	pthread_mutex_lock(&(philo->info->fork[philo->right]));
	print_log(philo, FORK);
	pthread_mutex_lock(&(philo->info->status_lock));
	philo->status = EATING;
	pthread_mutex_unlock(&(philo->info->status_lock));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->time_lock));
	philo->last_meal_time = philo->info->log;
	pthread_mutex_unlock(&(philo->info->time_lock));
	pthread_mutex_lock(&(philo->info->meal_lock));
	philo->meal_count += 1;
	pthread_mutex_unlock(&(philo->info->meal_lock));
	print_log(philo, NOTHING);
	pass_time(philo->info->eat);
	pthread_mutex_lock(&(philo->info->status_lock));
	philo->status = SLEEPING;
	pthread_mutex_unlock(&(philo->info->status_lock));
	pthread_mutex_unlock(&(philo->info->fork[philo->left]));
	pthread_mutex_unlock(&(philo->info->fork[philo->right]));
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->time_lock));
	philo->info->log = get_timestamp();
	pthread_mutex_unlock(&(philo->info->time_lock));
	print_log(philo, NOTHING);
	pass_time(philo->info->sleep);
	pthread_mutex_lock(&(philo->info->status_lock));
	philo->status = THINKING;
	pthread_mutex_unlock(&(philo->info->status_lock));
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->time_lock));
	philo->info->log = get_timestamp();
	pthread_mutex_unlock(&(philo->info->time_lock));
	print_log(philo, NOTHING);
}
