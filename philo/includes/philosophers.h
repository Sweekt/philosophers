/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:59:03 by beroy             #+#    #+#             */
/*   Updated: 2024/03/13 15:25:56 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	unsigned int	nbr_phil;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	int				nbr_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
}	t_philo;

// params_parser

int ft_is_num(char *str);
int ft_atoi(char *str);
int ft_check_args(char **av);

// philo_utils

// init


#endif