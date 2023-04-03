/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:54:07 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/27 12:04:32 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	check_dead_or_alive(t_philo *philo)
{
	size_t	last_meal_time;

	pthread_mutex_lock(&(philo->info->time_lock));
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&(philo->info->time_lock));
	if (get_timestamp() - last_meal_time >= philo->info->die)
	{
		print_log(philo, DIED);
		if (philo->info->philo_num == 1)
			pthread_mutex_unlock(&(philo->info->fork[philo->right]));
		return (1);
	}
	return (0);
}

static int	check_philo(t_philo *philo)
{
	int	meal_count;

	if (check_dead_or_alive(philo))
		return (1);
	if (philo->info->must_eat_flag)
	{
		pthread_mutex_lock(&(philo->info->meal_lock));
		meal_count = philo->meal_count;
		pthread_mutex_unlock(&(philo->info->meal_lock));
		if (meal_count != 0 && meal_count == philo->info->must_eat)
		{
			pthread_mutex_lock(&(philo->info->dead_or_alive_lock));
			philo->dead_or_alive = ENOUGH;
			pthread_mutex_unlock(&(philo->info->dead_or_alive_lock));
			return (1);
		}
	}
	return (0);
}

void	monitoring(t_philo *philo)
{
	int	check_status;

	while (1)
	{
		pthread_mutex_lock(&(philo->info->dead_or_alive_lock));
		check_status = philo->dead_or_alive;
		pthread_mutex_unlock(&(philo->info->dead_or_alive_lock));
		if (check_status == LIVE)
		{
			if (check_philo(philo))
				return ;
		}
		usleep(1000);
	}
	return ;
}
