/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:40:46 by beroy             #+#    #+#             */
/*   Updated: 2024/03/21 16:52:48 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_write(philo, RFORK, BLUE, 0);
	pthread_mutex_lock(philo->l_fork);
	ft_write(philo, LFORK, CYAN, 0);
	ft_write(philo, EAT, GREEN, 0);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = time_now();
	pthread_mutex_unlock(philo->meal_lock);
	philo->meals_eaten++;
	ft_usleep(philo->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think(t_philo *philo)
{
	ft_write(philo, SLEEP, PURPLE, 0);
	ft_usleep(philo->tts * 1000);
	ft_write(philo, THINK, YELLOW, 0);
	ft_usleep(500);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = time_now();
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);

	if ((philo->id - 1) % 2 == 1)
	{
		ft_write(philo, THINK, PURPLE, 0);
		ft_usleep(500);
	}
	while (*philo->status == ALIVE)
	{
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}
