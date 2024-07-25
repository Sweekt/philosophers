/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:13 by beroy             #+#    #+#             */
/*   Updated: 2024/07/22 16:39:43 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_forks	*fork_init(int nbr_phil)
{
	t_forks	*forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(t_forks) * nbr_phil);
	if (forks == NULL)
		return (NULL);
	while (i < nbr_phil)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL))
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i].fork);
			return (free(forks), NULL);
		}
		forks[i].f_state = AVAILABLE;
		i++;
	}
	return (forks);
}

void	mutex_destroyer(t_table *table, int state, int i)
{
	if (state < 2)
		pthread_mutex_destroy(&table->dead_lock);
	if (state < 1)
		pthread_mutex_destroy(&table->start_lock);
	if (state < 0)
		pthread_mutex_destroy(&table->write_lock);
	while (i-- > 0)
		pthread_mutex_destroy(&table->philo[i].meal_lock);
}

t_table	*table_init(t_philo *philo, int nbr_phil)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (NULL);
	if (pthread_mutex_init(&table->start_lock, NULL))
		return (mutex_destroyer(table, 1, 0), NULL);
	if (pthread_mutex_init(&table->dead_lock, NULL))
		return (mutex_destroyer(table, 2, 0), NULL);
	table->forks = fork_init(nbr_phil);
	if (table->forks == NULL)
		return (mutex_destroyer(table, 3, 0), free(table), NULL);
	table->philo = philo;
	table->status = 1;
	return (table);
}

void	content_init(t_philo *philo, t_table *table, char **av, int i)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->nbr_phil = ft_atoi(av[1]);
	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	if (av[5])
		philo->nbr_eat = ft_atoi(av[5]);
	else
		philo->nbr_eat = -1;
	philo->alive = ALIVE;
	philo->last_meal = time_now();
	philo->satisfied = 0;
	philo->initial_time = time_now();
	philo->write_lock = &table->write_lock;
	philo->start_lock = &table->start_lock;
	philo->dead_lock = &table->dead_lock;
}

t_table	*init(char **av)
{
	int		i;
	t_philo	*philo;
	t_table	*table;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (philo == NULL)
		return (NULL);
	table = table_init(philo, ft_atoi(av[1]));
	if (table == NULL)
		return (free(philo), NULL);
	while (i < ft_atoi(av[1]))
	{
		content_init(&philo[i], table, av, i);
		if (pthread_mutex_init(&philo[i].meal_lock, NULL))
			return (mutex_destroyer(table, 3, i), NULL);
		philo[i].r_fork = &table->forks[i];
		philo[i].status = &table->status;
		if (i != ft_atoi(av[1]) - 1)
			philo[i].l_fork = &table->forks[i + 1];
		else
			philo[i].l_fork = &table->forks[0];
		i++;
	}
	return (table);
}
