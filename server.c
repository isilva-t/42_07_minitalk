/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:05:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/26 18:13:52 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
#include "minitalk.h"

#define STRSIZE 128

typedef struct s_data
{
	char	data[STRSIZE];
	struct s_data	*prev;
	struct s_data	*next;
}		t_data;

int	mt_lstsize(t_data *lst)
{
	int		size;
	t_data	*counter;

	size = 0;
	counter = (t_data *)lst;
	while (counter)
	{
		size++;
		counter = counter->next;
	}
	return (size);
}

t_data	*mt_lstlast(t_data *lst)
{
	t_data	*last;
	int		size;

	last = (t_data *)lst;
	size = mt_lstsize(lst);
	while (size > 1)
	{
		last = last->next;
		size--;
	}
	return (last);
}

void	append_node(t_data **lst)
{
	t_data	*new;
	t_data	*last_node;

	if (!lst)
		return ;

	new = malloc(sizeof(*new));
	if(!new)
		return ;
	new->next = NULL;
	ft_bzero(new->data, STRSIZE);
	if (!(*lst))
	{
		//ft_printf("NO *lst\n");
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		//ft_printf("node in lst\n");
		last_node = mt_lstlast(*lst);
		last_node->next = new;
		new->prev = last_node;
	}
}

/*void free_lst(t_data *lst)
{
	t_data	*cur;
	t_data	*tmp;
	if (!lst)
		return ;
	cur = lst;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free (tmp);
	}
}*/


int	print_data(t_data **lst)
{
	t_data	*cur;
	t_data	*tmp;

	if (!lst || !*lst)
		return (0);
	cur = *lst;
	while (cur->prev)
		cur = cur->prev;
	while(cur)
	{
		//bytes +=ft_strlen(cur->data);
		ft_printf("%s", cur->data);
		tmp = cur;
		cur = cur->next;
		free (tmp);
	}
	return (1);
}

void	save_data(t_data **lst, char c, int i)
{
	while((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->data[i] = c;
}

static void	handle_sig(int signal, siginfo_t *sig, void *a)
{
	static unsigned int		b = 0;
	static int		i = -1;
	static unsigned char	c = 0;
	static t_data			*lst = NULL;

	(void)a;
	(void)sig;

	if (i == -1)
	{
		i++;
		append_node(&lst);
	}
	usleep(50);
	if (signal == SIGUSR2)
	{	
		c |= 1;
	}
	if (++b == 8)
	{
		b = 0;
		save_data(&lst, c, i);
		i++;
		//write(1, &c, 1);
		if (c == 0)
		{
			print_data(&lst);
			i = -1;
			lst = NULL;
			//write(1, "\n", 1);
			usleep(5000);
			kill(sig->si_pid, SIGUSR1);
			return ;
			//print_data(&lst);
		}
		c = 0;
		kill(sig->si_pid, SIGUSR2);
		return ;
	}
	else  
	{
		c <<= 1;
	}
	kill(sig->si_pid, SIGUSR2);

	if (i == STRSIZE -1)
	{
		i = -1;
	}
}
int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	ft_memset(&s, 0, sizeof(s));
	if (sigemptyset(&s.sa_mask) < 0)
		ft_printf("Error\n");
	s.sa_sigaction = handle_sig;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}
