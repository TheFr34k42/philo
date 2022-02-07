/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:25:53 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/07 13:14:32 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_ms(int time)
{
	usleep(time * 1000);
}

void	ft_write(t_philosopher *philo, char *msg, long long time)
{
	if (philo->args->stop != 1)
	{
		pthread_mutex_lock(&philo->args->write);
		printf("%lld philo %d %s", time - philo->args->t_start, philo->id, msg);
		pthread_mutex_unlock(&philo->args->write);
	}
}

long	ft_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_philosopher	*ft_philos_init(t_program_args *args)
{
	int				i;
	int				j;
	t_philosopher	*head;

	args->t_start = ft_time_now();
	j = 1;
	i = args->n_philo;
	head = ft_lstnew(j++, args);
	while (j <= i)
		ft_lstadd_back(&head, ft_lstnew(j++, args));
	return (head);
}

void	ft_create_threads(t_philosopher *philos)
{
	int	i;

	i = philos->args->n_philo;
	while (i--)
	{
		pthread_create(&philos->thread_id, NULL, &ft_routine, philos);
		philos->t_lastmeal = philos->args->t_start;
		philos = philos->next;
		usleep(50);
	}
}
