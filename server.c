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

void	append_node(t_data **lst, int *i)
{
	t_data	*new;
	t_data	*last_node;

	if (!lst)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		return ;
	new->next = NULL;
	ft_bzero(new->data, STR_SIZE);
	if (!(*lst))
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		last_node = mt_lstlast(*lst);
		last_node->next = new;
		new->prev = last_node;
	}
	*i = *i + 1;
}

void	print_free_and_reset_i(t_data **lst, int *i, int client_pid)
{
	t_data	*cur;
	t_data	*tmp;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	while (cur->prev)
		cur = cur->prev;
	while (cur)
	{
		ft_printf("%s\n", cur->data);
		tmp = cur;
		cur = cur->next;
		free (tmp);
	}
	*i = -1;
	*lst = NULL;
	lst = NULL;
	usleep(512);
	kill(client_pid, SIGUSR1);
}

void	save_byte(t_data **lst, char byte, int *i, unsigned int *bits)
{
	*bits = 0;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->data[*i] = byte;
	*i = *i + 1;
}

void	send_received_to_client_and_verify_i(int client_pid, int *i, void *a)
{
	kill(client_pid, SIGUSR2);
	if (*i == STR_SIZE -1)
		*i = -1;
	(void)a;
}

static void	handle_sig(int signal, siginfo_t *sig, void *a)
{
	static unsigned int		bits = 0;
	static int				i = -1;
	static unsigned char	byte = 0;
	static t_data			*lst = NULL;

	if (i == -1)
		append_node(&lst, &i);
	usleep(128);
	if (signal == SIGUSR2)
		byte |= 1;
	if (++bits == 8)
	{
		save_byte(&lst, byte, &i, &bits);
		if (byte == 0)
		{
			print_free_and_reset_i(&lst, &i, sig->si_pid);
			return ;
		}
		byte = 0;
		kill(sig->si_pid, SIGUSR2);
		return ;
	}
	else
		byte <<= 1;
	send_received_to_client_and_verify_i(sig->si_pid, &i, a);
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
