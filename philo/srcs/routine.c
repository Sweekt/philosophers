/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:40:46 by beroy             #+#    #+#             */
/*   Updated: 2024/03/20 14:17:34 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_write(philo, RFORK, BLUE);
	pthread_mutex_lock(philo->l_fork);
	ft_write(philo, LFORK, CYAN);
	ft_write(philo, EAT, GREEN);
	philo->last_meal = time_now();
	philo->meals_eaten++;
	ft_usleep(philo->tte);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think(t_philo *philo)
{
	ft_write(philo, SLEEP, PURPLE);
	ft_usleep(philo->tts);
	ft_write(philo, THINK, YELLOW);
	ft_usleep(500);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	philo->last_meal = time_now();
	if ((philo->id - 1) % 2 == 1)
	{
		ft_write(philo, THINK, PURPLE);
		ft_usleep(500);
	}
	while (philo->alive == ALIVE)
	{
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}
