/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:59:03 by beroy             #+#    #+#             */
/*   Updated: 2024/03/18 16:59:01 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200
# define ALIVE 1

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	unsigned int	nbr_phil;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	nbr_eat;
	unsigned int 	alive;
	long int		last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
}	t_philo;

// main

void		ft_display(t_philo *philo);

// params_parser

int			ft_is_num(char *str);
int			ft_atoi(char *str);
int			ft_check_args(char **av);

// routine

void		eat(t_philo *philo);
void		sleep_think(t_philo *philo);
void		*routine(void *data);

// init

void		content_init(t_philo *philo, int ac, char **av, int i);
t_philo		*philo_init(int ac, char **av);

// time

long int	time_now(void);
void		ft_usleep(long int time);

#endif