/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:04 by beroy             #+#    #+#             */
/*   Updated: 2024/07/22 19:05:42 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	chk_meal(t_philo *philo)
{
	long int	meals;

	pthread_mutex_lock(&philo->meal_lock);
	meals = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (meals);
}

int	chk_nb_meal(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->meal_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_lock);
	return (meals);
}

void	set_death(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->dead_lock);
	philo->alive = status;
	pthread_mutex_unlock(philo->dead_lock);
}

int take_fork(t_philo *philo)
{
	int	state;

	state = AVAILABLE;
	pthread_mutex_lock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->r_fork->fork);
	if (philo->l_fork->f_state == AVAILABLE && philo->r_fork->f_state == AVAILABLE)
	{
		philo->l_fork->f_state = TAKEN;
		philo->r_fork->f_state = TAKEN;
		state = TAKEN;
	}
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
	return (state);
}

int give_fork(t_philo *philo)
{
	int	state;

	state = TAKEN;
	pthread_mutex_lock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->r_fork->fork);
	if (philo->l_fork->f_state == TAKEN && philo->r_fork->f_state == TAKEN)
	{
		philo->l_fork->f_state = AVAILABLE;
		philo->r_fork->f_state = AVAILABLE;
		state = AVAILABLE;
	}
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_unlock(&philo->l_fork->fork);
	return (state);
}