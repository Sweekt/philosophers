/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:48:50 by beroy             #+#    #+#             */
/*   Updated: 2024/02/21 08:48:50 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_display(t_params *params)
{
	printf("Number of philosophers: %d\n", params->nbr_phil);
	printf("Time to die: %d\n", params->ttd);
	printf("Time to eat: %d\n", params->tte);
	printf("Time to sleep: %d\n", params->tts);
	printf("Number of time to eat: %d\n", params->nbr_eat);
}
