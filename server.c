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

#include "minitalk.h"

typedef struct s_data
{
	char	data[4096];
	struct s_data	*prev;
	struct s_data	*next;
}		t_data;

void	append_node(t_data **lst)
{
	t_data	*new;

	if (!lst)
		return ;

	new = malloc(sizeof(*new));
	if(!new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		new->prev = *lst;
		(*lst)->next = new;
	}
}

void	print_data(t_data **lst)
{
	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		if ((*lst)->prev != NULL)
			*lst = (*lst)->prev;
	}
	while(lst)
	{
		ft_printf("%s", (*lst)->data);
		*lst = (*lst)->next;
	}
}

static void	handle_sig(int signal, siginfo_t *sig, void *a)
{
	static unsigned int		b = 0;
	static unsigned int		i = 0;
	static unsigned char	c = 0;
	static t_data			*lst = NULL;

	(void)a;
	sig->si_signo = 0;
	if (sig->si_signo == 0)
		sig->si_signo = 0;
	
	if (i == 0)
	{
		write(1, "z\n", 2);
		i++;
		append_node(&lst);
	}
	if (signal == SIGUSR2)
	{	
		c |= 1;
	}
	if (++b == 8)
	{
		b = 0;
		i++;
		lst->data[i - 1] = c;
		write(1, &c, 1);
		if (c == 0)
		{
			print_data(&lst);
			write(1, "\n", 3);
			//print_data(&lst);
		}
		c = 0;
		kill(sig->si_pid, SIGUSR1);
		return ;
	}
	else
	{
		c <<= 1;
	}
	kill(sig->si_pid, SIGUSR2);
	
/*	if (i == 4095)
	{
		lst->data[i - 1] = '\0';
		i = 0;
	}*/
}

int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	if (sigemptyset(&s.sa_mask) < 0)
		ft_printf("Error\n");
	s.sa_sigaction = handle_sig;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}
