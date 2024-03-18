/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:13 by beroy             #+#    #+#             */
/*   Updated: 2024/03/18 17:30:50 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	content_init(t_philo *philo, int ac, char **av, int i)
{
	philo->id = i;
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
	philo->last_meal = 0;
}

t_philo	*philo_init(int ac, char **av)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t write_lock;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (philo == NULL)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (forks == NULL)
		return (free(philo), NULL);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		content_init(&philo[i], ac, av, i);
		philo[i].write_lock = &write_lock;
		philo[i].r_fork = &forks[i];
		if (i != ft_atoi(av[1]) - 1)
			philo[i].l_fork = &forks[i + 1];
		else
			philo[i].l_fork = &forks[0];
		i++;
	}
	return (philo);
}