/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:35:59 by beroy             #+#    #+#             */
/*   Updated: 2024/03/20 14:01:06 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_write(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(philo->write_lock);
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
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)data;
	i = 0;
	while (check_status(philo) == ALIVE)
	{
		if (philo[i].last_meal >= philo[i].ttd)
			philo[i].alive = DEAD;
		ft_usleep(500);
		i++;
		if (i == philo[0].nbr_phil)
			i = 0;
	}
	return (NULL);
}
