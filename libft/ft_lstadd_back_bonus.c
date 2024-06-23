/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:19:35 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:13:44 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_lst	*ft_last(t_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*tail;

	tail = *lst;
	tail = ft_last(tail);
	if (new != NULL && tail != NULL)
	{
		tail->next = new;
	}
	else if (new != NULL)
	{
		tail = new;
		*lst = tail;
	}
}
