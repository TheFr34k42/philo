/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:14:50 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/07 13:15:30 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*ft_lstnew(int id, t_program_args *args)
{
	t_philosopher	*new;

	new = malloc(sizeof(t_philosopher));
	pthread_mutex_init(&new->fork, NULL);
	new->id = id;
	new->next = new;
	new->n_meals = 0;
	new->args = args;
	new->iseating = 0;
	return (new);
}

t_philosopher	*ft_lstlast(t_philosopher *head)
{
	t_philosopher	*tmp;

	tmp = head;
	while (1 && head)
	{
		head = head->next;
		if (head->next == tmp)
			return (head);
	}
	return (head);
}

void	ft_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher	*last;

	if (lst)
	{
		if (new)
		{
			last = ft_lstlast(*lst);
			last->next = new;
			new->next = (*lst);
		}
	}
	else
		(*lst) = new;
}

void	ft_args_init(t_program_args *args, char **argv)
{
	args->n_philo = atoi(argv[0]);
	args->t_die = atoi(argv[1]);
	args->t_eat = atoi(argv[2]);
	args->t_sleep = atoi(argv[3]);
	args->stop = 0;
	if (argv[4])
		args->n_meals = atoi(argv[4]);
	else
		args->n_meals = -1;
	pthread_mutex_init(&args->write, NULL);
}

int	main(int argc, char **argv)
{
	t_program_args	*args;
	t_philosopher	*node;

	args = malloc(sizeof(t_program_args));
	if (argc >= 5 && argc <= 6)
	{
		ft_args_init(args, &argv[1]);
		node = ft_philos_init(args);
		ft_create_threads(node);
		ft_routine_manager(node);
	}
	else
	{
		printf("Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}
