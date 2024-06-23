/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:31:08 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:13:34 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_lst	*ft_lstnew(void *content)
// {
// 	t_lst	*node;

// 	node = (t_lst *)malloc(1 * sizeof(t_lst));
// 	if (node == NULL)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

void	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_lst	*begin = NULL;
// 	int		i = 3;
// 	int		*content = &i;
// 	t_lst	elem;

// 	ft_lstnew(content);
// 	ft_lstadd_front(&begin, &elem);
// }