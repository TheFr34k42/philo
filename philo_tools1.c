/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:28:27 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/07 16:25:08 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_manager(t_philosopher *philos)
{
	while (1)
	{
		if (!philos->args->n_philo || !philos->args->n_philo)
			return ;
		if (philos->id && (ft_time_now()
				- philos->t_lastmeal > philos->args->t_die)
			&& philos->iseating == 0)
		{
			ft_write(philos, "died\n", ft_time_now());
			pthread_mutex_lock(&philos->args->write);
			philos->args->stop = 1;
			return ;
		}
		philos = philos->next;
	}
}

void	*ft_routine(void *arg)
{
	t_philosopher	*philos;

	philos = (t_philosopher *) arg;
	while (philos->args->n_meals != philos->n_meals)
	{
		pthread_mutex_lock(&philos->fork);
		ft_write(philos, "has taken a fork\n", ft_time_now());
		pthread_mutex_lock(&philos->next->fork);
		ft_write(philos, "is eating\n", ft_time_now());
		philos->iseating = 1;
		philos->t_lastmeal = ft_time_now();
		ft_sleep_ms(philos->args->t_eat);
		pthread_mutex_unlock(&philos->fork);
		pthread_mutex_unlock(&philos->next->fork);
		philos->n_meals++;
		philos->iseating = 0;
		ft_write(philos, "is sleeping\n", ft_time_now());
		ft_sleep_ms(philos->args->t_sleep);
		ft_write(philos, "is thinking\n", ft_time_now());
	}
	philos->args->n_philo--;
	philos->id = 0;
	return (NULL);
}
