/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:05:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/22 17:31:37 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_sig(int signal, siginfo_t *sig, void *a)
{
	static unsigned int		i = 0;
	static unsigned char	c = 0;

	(void)a;
	sig->si_signo = 0;
	if (sig->si_signo == 0)
		sig->si_signo = 0;
	if (signal == SIGUSR2)
		c |= 1;
	if (++i == 8)
	{
		i = 0;
		ft_putchar_fd(c, 1);
		ft_putchar_fd('\0', 1);
		c = 0;
		return ;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	s.sa_sigaction = handle_sig;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	while (1)
		pause();
	return (0);
}
