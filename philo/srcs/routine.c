/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:40:46 by beroy             #+#    #+#             */
/*   Updated: 2024/07/25 17:18:44 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	while (take_fork(philo) == AVAILABLE)
		ft_usleep(1000, philo);
	ft_write(philo, EAT, GREEN, 0);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time_now();
	ft_usleep(philo->tte * 1000, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	give_fork(philo);
}

void	sleep_think(t_philo *philo)
{
	ft_write(philo, SLEEP, PURPLE, 0);
	ft_usleep(philo->tts * 1000, philo);
	ft_write(philo, THINK, YELLOW, 0);
	ft_usleep(500, philo);
}

int	ft_status(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->status == DEAD)
		state = DEAD;
	else
		state = ALIVE;
	pthread_mutex_unlock(philo->dead_lock);
	return (state);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time_now();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	if ((philo->id - 1) % 2 == 1)
	{
		ft_write(philo, THINK, PURPLE, 0);
		ft_usleep(1000, philo);
	}
	while (ft_status(philo) == ALIVE)
	{
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}

void	*routine_solo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time_now();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	pthread_mutex_lock(&philo->r_fork->fork);
	ft_write(philo, RFORK, BLUE, 0);
	while (ft_status(philo) == ALIVE)
		ft_usleep(1000, philo);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (NULL);
}
