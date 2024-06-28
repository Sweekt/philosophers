/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:35:59 by beroy             #+#    #+#             */
/*   Updated: 2024/06/28 18:10:03 by beroy            ###   ########.fr       */
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
		if (ft_status(&philo[i]) == DEAD)
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
	ft_usleep(table->philo[0].tte * 2000);
	i = 0;
	while (check_status(table->philo) == ALIVE)
	{
		if (time_now() - chk_meal(&table->philo[i]) >= table->philo[i].ttd)
			set_status(&table->philo[i], DEAD);
		if (table->philo[i].nbr_eat != -1
			&& chk_nb_meal(&table->philo[i]) >= table->philo[i].nbr_eat)
			table->philo[i].satisfied = 1;
		ft_usleep(500);
		i++;
		if (i == table->philo[0].nbr_phil)
			i = 0;
	}
	return (NULL);
}
