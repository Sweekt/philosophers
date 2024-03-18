/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:58:57 by beroy             #+#    #+#             */
/*   Updated: 2024/03/18 17:13:27 by beroy            ###   ########.fr       */
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
	t_philo			*philo;
	unsigned int	i;

	if (ac < 5 || ac > 6)
		return (printf("Wrong arguments input!\n"), 0);
	if (ft_check_args(av) == 1)
		return (0);
	philo = philo_init(ac, av);
	if (philo == NULL)
		return (printf("Malloc failed!\n"), 0);
	ft_display(philo);
	i = 0;
	while (i < philo[0].nbr_phil)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	while (ALIVE)
		;
	return (0);
}
