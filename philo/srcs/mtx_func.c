/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:10:04 by beroy             #+#    #+#             */
/*   Updated: 2024/06/28 18:10:04 by beroy            ###   ########.fr       */
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

void	set_status(t_philo *philo, int status)
{
	pthread_mutex_lock(philo->dead_lock);
	philo->alive = status;
	pthread_mutex_unlock(philo->dead_lock);
}