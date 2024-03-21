/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:57 by beroy             #+#    #+#             */
/*   Updated: 2024/03/21 13:53:36 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_display(t_philo *philo)
{
	unsigned int i;

	i = 0;
	while (i < philo[i].nbr_phil)
	{
		printf("ID= %d\n", philo[i].id);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table			*table;
	unsigned int	i;
	pthread_t 		monitor;

	if (ac < 5 || ac > 6)
		return (printf("Wrong arguments input!\n"), 0);
	if (ft_check_args(av) == 1)
		return (0);
	table = init(ac, av);
	if (table == NULL)
		return (printf("Malloc failed!\n"), 0);
	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->philo[0].nbr_phil)
	{
		pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i]);
		i++;
	}
	pthread_mutex_unlock(&table->start_lock);
	pthread_create(&monitor, NULL, monitoring, table);
	while (ALIVE)
		;
	return (0);
}
