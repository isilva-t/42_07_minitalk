/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:56:10 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/22 17:34:00 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_kills(int pid, char *str)
{
	int		i;
	char	c;

	ft_printf("pid: %d\n", pid);
	ft_printf("str: %s\n", str);
	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 3 || ft_strlen(av[1]) == 0)
	{
		ft_printf("Please check your ARG's!\n");
		return (1);
	}
	send_kills(ft_atoi(av[1]), av[2]);
	return (0);
}
