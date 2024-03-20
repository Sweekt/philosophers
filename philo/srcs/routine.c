/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:40:46 by beroy             #+#    #+#             */
/*   Updated: 2024/03/18 17:23:44 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->write_lock);
	printf("%li: Philo %d is eating...\n", time_now(), philo->id);
	pthread_mutex_unlock(philo->write_lock);
	philo->last_meal = time_now();
	philo->meals_eaten++;
	ft_usleep(philo->tte);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("Philo %d is sleeping...\n", philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_usleep(philo->tts);
	pthread_mutex_lock(philo->write_lock);
	printf("Philo %d is thinking...\n", philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_meal = time_now();
	while (philo->alive == ALIVE)
	{
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}