/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:13 by beroy             #+#    #+#             */
/*   Updated: 2024/03/13 15:18:31 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	philo_init(int ac, char **av)
{
	params->nbr_phil = ft_atoi(av[1]);
	params->ttd = ft_atoi(av[2]);
	params->tte = ft_atoi(av[3]);
	params->tts = ft_atoi(av[4]);
	if (ac == 6)
		params->nbr_eat = ft_atoi(av[5]);
	else
		params->nbr_eat = -1;
}