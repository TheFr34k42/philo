#include "Philosophers.h"
#include <unistd.h>


t_philosopher *ft_lstnew(int num)
{
	t_philosopher *new;
	new = malloc(sizeof(t_philosopher));
	new->num = num;
	new->next = new;
	new->n_meals = 0;
	gettimeofday(&new->t_start, NULL);
	return (new);
}

t_philosopher *ft_lstlast(t_philosopher *head)
{
	t_philosopher *tmp;

	tmp = head;
	while (1 && head)
	{
		head = head->next;
		if (head->next == tmp)
			return (head);
	}
	return (head);
}

void ft_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher *last;
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

void ft_args_init(t_program_args *args, char **argv)
{
	args->n_philo = atoi(argv[0]);
	args->t_die = atoi(argv[1]);
	args->t_eat = atoi(argv[2]);
	args->t_sleep = atoi(argv[3]);
	gettimeofday(&args->t_now, NULL);
	if (argv[4])
		args->n_meals = atoi(argv[4]);
	else
		args->n_meals = -1;
}

int main(int argc, char **argv)
{

	t_program_args *args;
	args = malloc(sizeof(t_program_args));
	if (argc >= 5 && argc <= 6)
	{
		ft_args_init(args, &argv[1]);
		printf("%d ", args->n_philo);
		printf("%d ", args->t_die);
		printf("%d ", args->t_eat);
		printf("%d ", args->t_sleep);
		printf("%d\n", args->n_meals);
	}
	
	t_philosopher *node;
	t_philosopher *node1;
	t_philosopher *node2;
	t_philosopher *node3;
	t_philosopher *head;

	node = ft_lstnew(10);
	node1 = ft_lstnew(25);
	node2 = ft_lstnew(205);
	node3 = ft_lstnew(1000);
	ft_lstadd_back(&node,node1);
	ft_lstadd_back(&node,node2);
	ft_lstadd_back(&node,node3);
	printf("last : %d\n",ft_lstlast(node)->num);
	// node->next = node1;
	// node1->next = node;
	head = node;
	
	// struct timeval current_time, end;
	// gettimeofday(&current_time, NULL);
	while (1 && node)
	{
		printf("%d ",node->num);
		node = node->next;
		if (head == node)
		{
			printf("\n");
			break;
		}
	}
	// printf("seconds : %ld\nmicro seconds : %d\n",current_time.tv_sec, current_time.tv_usec);
	// sleep(10);
	// gettimeofday(&end, NULL);
	// printf("seconds : %ld\nmicro seconds : %d\n",(end.tv_sec - current_time.tv_sec), (end.tv_usec - current_time.tv_usec));
	return 0;
}
