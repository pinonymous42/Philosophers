/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:55:13 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/27 12:04:54 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	mutex_array_init(t_info *info)
{
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (info->philo == NULL)
		return (1);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->philo_num);
	if (info->fork == NULL)
		return (1);
	if (pthread_mutex_init(&(info->time_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(info->log_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(info->meal_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(info->dead_or_alive_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(info->status_lock), NULL))
		return (1);
	return (0);
}

static int	philo_init(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		info->philo[i].number = i + 1;
		info->philo[i].status = THINKING;
		info->philo[i].dead_or_alive = LIVE;
		if (i == 0)
		{
			info->philo[i].left = info->philo_num - 1;
			info->philo[i].right = 0;
		}
		else
		{
			info->philo[i].left = i - 1;
			info->philo[i].right = i;
		}
		info->philo[i].info = info;
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (1);
		info->philo[i].last_meal_time = info->log;
		info->philo[i].meal_count = 0;
	}
	return (0);
}

int	info_init(t_info *info, int argc, char **argv)
{
	info->philo_num = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->start = get_timestamp();
	info->log = get_timestamp();
	if (argc == 6)
	{
		info->must_eat_flag = 1;
		info->must_eat = ft_atoi(argv[5]);
	}
	else
	{
		info->must_eat_flag = 0;
		info->must_eat = 0;
	}
	if (mutex_array_init(info))
		return (1);
	if (philo_init(info))
		return (1);
	return (0);
}
