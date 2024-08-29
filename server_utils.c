/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:58:57 by isilva-t          #+#    #+#             */
/*   Updated: 2024/08/28 18:00:01 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	append_node(t_data **lst, int *i)
{
	t_data	*new;

	if (!lst || !i)
		return ;
	new = malloc(sizeof(*new));
	if (!new)
		return ;
	new->next = NULL;
	ft_bzero(new->data, STR_SIZE);
	if (!(*lst))
	{
		new->begin = new;
		*lst = new;
	}
	else
	{
		new->begin = (*lst)->begin;
		(*lst)->next = new;
		*lst = new;
	}
	*i = *i + 1;
}
