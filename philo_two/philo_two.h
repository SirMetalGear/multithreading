/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorette <mlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:00:02 by mlorette          #+#    #+#             */
/*   Updated: 2021/03/30 11:15:02 by mlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>

typedef struct	s_data
{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				eat_times;
}				t_data;

typedef struct	s_inside
{
	long long		start_time;
	long long		prev_eat;
	int				monitor_status;
	struct timeval	tv;
	int				turn;
	int				finish_eating;
	t_data			philo;
}				t_inside;

typedef struct	s_all
{
	int				turn;
	t_data			philo;
	long long		start_time;
	long long		*prev_eat;
	pthread_t		*thread;
	pthread_t		monitor;
	sem_t			*fork_sem;
	sem_t			*eat_sem;
	sem_t			*write_sem;
	sem_t			*turn_sem;
	sem_t			*time_sem;
	int				thread_status;
	int				death_status;
	int				eating_finished;
}				t_all;

int				ft_atoi(char *str);
int				all_num(char **str);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);
size_t			ft_strlen(const char *str);
int				philo_write(int turn, long long current_time, t_all *all,
														const char *str);
void			ft_putnbr(ssize_t n);
void			ft_putstr(char *s);
long long		get_time(t_all *all, struct timeval *tv);
int				monitor(t_all *all);
int				monitor_and_struct_init(t_inside *inside, t_all *all);
int				thread_start(t_all *all);
int				cleaner(t_all *all);

#endif
