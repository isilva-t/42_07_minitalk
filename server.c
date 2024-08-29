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

void	print_free_and_reset_i(t_data **lst, int *i, int *client_pid)
{
	t_data	*tmp;

	if (!lst || !*lst || !i || !client_pid)
		return ;
	*lst = (*lst)->begin;
	while (*lst)
	{
		tmp = *lst;
		ft_printf("%s", (*lst)->data);
		*lst = (*lst)->next;
		free (tmp);
	}
	*i = -1;
	*lst = NULL;
	lst = NULL;
	usleep(512);
	kill(*client_pid, SIGUSR1);
}

void	save_byte(t_data **lst, unsigned char *byte, int *i, unsigned int *bits)
{
	if (!lst || !*lst || !byte || !i || !bits)
		return ;
	(*lst)->data[*i] = *byte;
	*bits = 0;
	*i = *i + 1;
}

void	send_sigusr2_to_client_and_verify_i(int *client_pid, int *i, void *a)
{
	if (!i || !client_pid)
		return ;
	kill(*client_pid, SIGUSR2);
	if (*i == STR_SIZE -1)
		*i = -1;
	(void)a;
}

static void	handle_sig(int signal, siginfo_t *sig, void *a)
{
	static int				i = -1;
	static unsigned int		bits = 0;
	static unsigned char	byte = 0;
	static t_data			*lst = NULL;

	if (i == -1)
		append_node(&lst, &i);
	usleep(128);
	if (signal == SIGUSR2)
		byte |= 1;
	if (++bits == 8)
	{
		save_byte(&lst, &byte, &i, &bits);
		if (byte == 0)
		{
			print_free_and_reset_i(&lst, &i, &sig->si_pid);
			return ;
		}
		byte = 0;
		send_sigusr2_to_client_and_verify_i(&sig->si_pid, &i, a);
		return ;
	}
	else
		byte <<= 1;
	send_sigusr2_to_client_and_verify_i(&sig->si_pid, &i, a);
}

int	main(void)
{
	struct sigaction	s;
	int					server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\nTry burn me! %s\n", server_pid, EMOJI_1);
	ft_printf("press \"Ctrl + C\" to close Server, ");
	ft_printf("but only when I'm idle! %s\n\n", EMOJI_2);
	ft_memset(&s, 0, sizeof(s));
	if (sigemptyset(&s.sa_mask) < 0)
		ft_printf("Error initializing sa_mask!\n");
	s.sa_sigaction = handle_sig;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}
