/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:38:38 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:13:20 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void*))
{
	t_lst	*tail;

	while (*lst != NULL)
	{
		tail = *lst;
		*lst = tail->next;
		del(tail->content);
		free(tail);
	}
}
