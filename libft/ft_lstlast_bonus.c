/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:12:28 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:12:46 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_lst;

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

// void	ft_lstadd_front(t_lst **lst, t_lst *new)
// {
// 	new->next = *lst;
// 	*lst = new;
// }

t_lst	*ft_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_lst	*head;
// 	int		cont = 5;
// 	int		*content = &cont;
// 	t_lst	*node2;
// 	int		cont2 = 3;
// 	int		*content2 = &cont2;
// 	t_lst	*node3;
// 	int		cont3 = 1;
// 	int		*content3 = &cont3;
// 	t_lst	*tail;

// 	head = ft_lstnew(content);
// 	node2 = ft_lstnew(content2);
// 	node3 = ft_lstnew(content3);

// 	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node3);

//     tail = head;
// 	tail = ft_lstlast(tail);
// }