/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:05:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/28 18:00:30 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_free_and_reset_i(t_data **lst, int *i, int client_pid)
{
	t_data	*cur;
	t_data	*tmp;

	if (!lst || !*lst || !i)
		return ;
	cur = (*lst)->begin;
	while (cur)
	{
		ft_printf("%s", cur->data);
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
	if (!lst || !*lst || !i || !bits)
		return ;
	*bits = 0;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->data[*i] = byte;
	*i = *i + 1;
}

void	send_sigusr2_to_client_and_verify_i(int client_pid, int *i, void *a)
{
	if (!i)
		return ;
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
		send_sigusr2_to_client_and_verify_i(sig->si_pid, &i, a);
		return ;
	}
	else
		byte <<= 1;
	send_sigusr2_to_client_and_verify_i(sig->si_pid, &i, a);
}

int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\nTry burn me! \xF0\x9F\x94\xA5\n", pid);
	ft_printf("Ctrl + C to close Server\xF0\x9F\x98\x8A");
	ft_printf("but only when I message you! \xF0\x9F\x98\x80\n\n");
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
