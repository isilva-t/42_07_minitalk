/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:06:25 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/26 18:00:13 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libs/libft/libft.h"
# include "./libs/ft_printf/ft_printf.h"

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define STR_SIZE 4096
# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	char	data[STR_SIZE];
	struct s_data	*prev;
	struct s_data	*next;
}		t_data;

#endif
