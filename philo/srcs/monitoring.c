/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:35:59 by beroy             #+#    #+#             */
/*   Updated: 2024/04/11 13:26:26 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_write(t_philo *philo, char *str, char *color, int stop)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->status == ALIVE)
	{
		printf("%li%s %d %s\033[0m\n", time_now() - philo->initial_time, color,
			philo->id, str);
		if (stop == 1)
			*philo->status = 0;
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->write_lock);
}

int	check_status(t_philo *philo)
{
	unsigned int	i;
	unsigned int	satisfied;

	i = 0;
	satisfied = 0;
	while (i < philo[0].nbr_phil)
	{
		if (philo[i].alive == DEAD)
		{
			ft_write(&philo[i], DIED, RED, 1);
			return (DEAD);
		}
		if (philo[i].satisfied == 1)
			satisfied++;
		i++;
	}
	if (satisfied == philo[0].nbr_phil)
	{
		ft_write(&philo[0], SATISFIED, BLACK, 1);
		return (DEAD);
	}
	return (ALIVE);
}

void	*monitoring(void *data)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)data;
	pthread_mutex_lock(&table->start_lock);
	pthread_mutex_unlock(&table->start_lock);
	ft_usleep(table->philo[0].ttd * 1000);
	i = 0;
	while (check_status(table->philo) == ALIVE)
	{
		pthread_mutex_lock(&table->philo[i].meal_lock);
		if (time_now() - table->philo[i].last_meal >= table->philo[i].ttd)
			table->philo[i].alive = DEAD;
		if (table->philo[i].nbr_eat != -1
			&& table->philo[i].meals_eaten >= table->philo[i].nbr_eat)
			table->philo[i].satisfied = 1;
		pthread_mutex_unlock(&table->philo[i].meal_lock);
		ft_usleep(500);
		i++;
		if (i == table->philo[0].nbr_phil)
			i = 0;
	}
	return (NULL);
}
