/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:02:40 by gstronge          #+#    #+#             */
/*   Updated: 2024/05/10 20:12:23 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*node;

	node = (t_lst *)malloc(1 * sizeof(t_lst));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	content = 5;
// 	t_lst	*n1;

// 	n1 = ft_lstnew(&content);
// 	printf();
// }