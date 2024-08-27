/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:56:10 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/26 18:12:18 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_kills(int pid, char *str)
{
	int		i;
	char	c;

	i = 8;
	ft_printf("Server PID: %d\n", pid);
	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				kill(pid, SIGUSR2);
			}
			else
			{
				kill(pid, SIGUSR1);
			}
			pause();
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		pause();
	}
}

static void	client_handle(int signal, siginfo_t *sig, void *a)
{
	static unsigned int	n_bits = 0;
	(void)sig;
	(void)a;
	if (signal == SIGUSR2)
		n_bits++;
	else if (signal == SIGUSR1)
	{
		n_bits++;
		ft_printf("\nServer received %d bytes!\n", n_bits / 8);
		exit (0);
	}

}

int	main(int ac, char **av)
{
	struct sigaction	s;
	int					pid;

	if (ac != 3 || ft_strlen(av[1]) == 0)
	{
		ft_printf("Please check your ARG's!\n");
		return (1);
	}

	pid = getpid();
	//ft_printf("\n\nBytes to send: %d bytes\n", ft_strlen(av[2]) + 1);
	ft_printf("Client PID: %d\n", pid);
	ft_memset(&s, 0, sizeof(s));
	s.sa_sigaction = client_handle;
	s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s, NULL);
	sigaction(SIGUSR2, &s, NULL);
	send_kills(ft_atoi(av[1]), av[2]);
	return (0);
}
