/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:26:05 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:13:01 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lst *lst, void (*f)(void *))
{
	t_lst	*node;

	node = lst;
	if (lst == NULL)
		return ;
	while (node->next)
	{
		f(node->content);
		node = node->next;
	}
	f(node->content);
}
