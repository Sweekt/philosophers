/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:35:59 by beroy             #+#    #+#             */
/*   Updated: 2024/03/19 14:55:25 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int check_status(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo[0].nbr_phil)
	{
		if (philo[i].alive == DEAD)
			return (printf("Philosopher %d died from a lack of spaghetti... :(\n", philo[i].id), DEAD);
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
