/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:06:18 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:12:06 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int		listlen;

	listlen = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		listlen++;
	}
	return (listlen);
}
