/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:35:59 by beroy             #+#    #+#             */
/*   Updated: 2024/03/21 15:58:45 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_write(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%li: ", time_now());
	printf("%s", color);
	printf("Philosopher %d %s\n", philo->id, str);
	printf("\033[0m");
	pthread_mutex_unlock(philo->write_lock);
}

int check_status(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo[0].nbr_phil)
	{
		if (philo[i].alive == DEAD)
		{
			ft_write(&philo[i], DIED, RED);
			return (DEAD);
		}
		i++;
	}
	return (ALIVE);
}

void	*monitoring(void *data)
{
	t_table			*table;
	unsigned int	i;

	table = (t_table *)data;
	i = 0;
	while (check_status(table->philo) == ALIVE)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (time_now() - table->philo[i].last_meal >= table->philo[i].ttd)
			table->philo[i].alive = DEAD;
		pthread_mutex_unlock(&table->meal_lock);
		ft_usleep(500);
		i++;
		if (i == table->philo[0].nbr_phil)
			i = 0;
	}
	return (NULL);
}
