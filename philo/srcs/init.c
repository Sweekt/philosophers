/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:13 by beroy             #+#    #+#             */
/*   Updated: 2024/04/10 11:31:48 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_mutex_t 	*fork_init(int nbr_phil)
{
	pthread_mutex_t *forks;
	int 			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nbr_phil);
	if (forks == NULL)
		return (NULL);
	while (i < nbr_phil)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i]);
			return (free(forks), NULL);
		}
		i++;
	}
	return (forks);
}

void	mutex_destroyer(t_table *table, int state)
{
	if (state < 2)
		pthread_mutex_destroy(&table->meal_lock);
	if (state < 1)
		pthread_mutex_destroy(&table->start_lock);
	if (state < 0)
		pthread_mutex_destroy(&table->write_lock);
}

t_table	*table_init(t_philo *philo, int nbr_phil)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (NULL);
	if (pthread_mutex_init(&table->start_lock, NULL))
		return (mutex_destroyer(table, 1), NULL);
	if (pthread_mutex_init(&table->meal_lock, NULL))
		return (mutex_destroyer(table, 2), NULL);
	table->forks = fork_init(nbr_phil);
	if (table->forks == NULL)
		return (mutex_destroyer(table, 3), free(table), NULL);
	table->philo = philo;
	table->status = 1;
	return (table);
}

void	content_init(t_philo *philo, int ac, char **av, int i)
{
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->nbr_phil = ft_atoi(av[1]);
	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	if (ac == 6)
		philo->nbr_eat = ft_atoi(av[5]);
	else
		philo->nbr_eat = -1;
	philo->alive = ALIVE;
	philo->last_meal = time_now();
	philo->satisfied = 0;
	philo->initial_time = time_now();
}

t_table	*init(int ac, char **av)
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
		content_init(&philo[i], ac, av, i);
		philo[i].write_lock = &table->write_lock;
		philo[i].start_lock = &table->start_lock;
		philo[i].meal_lock = &table->meal_lock;
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
