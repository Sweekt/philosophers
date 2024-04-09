/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:57 by beroy             #+#    #+#             */
/*   Updated: 2024/03/21 21:02:28 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int join_n_free(t_table *table, pthread_t monitor, unsigned int i)
{
	pthread_join(monitor, NULL);
	while (i-- > 0)
		pthread_join(table->philo[i].thread, NULL);
	free(table->forks);
	free(table->philo);
	free(table);
	return (0);
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
	pthread_create(&monitor, NULL, monitoring, table);
	pthread_mutex_unlock(&table->start_lock);
	return (join_n_free(table, monitor, i));
}
