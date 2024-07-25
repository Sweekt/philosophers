/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:34:36 by beroy             #+#    #+#             */
/*   Updated: 2024/07/25 17:26:17 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long int	time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(long int time, t_philo *philo)
{
	long int	start_time;

	start_time = time_now();
	while ((time_now() - start_time) < time / 1000)
	{
		if (ft_status(philo) == DEAD)
			return ;
		usleep(150);
	}
}
