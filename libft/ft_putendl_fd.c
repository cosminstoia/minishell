/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:54:01 by gstronge          #+#    #+#             */
/*   Updated: 2024/03/10 23:54:01 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	write(fd, s, count);
	write(fd, "\n", 1);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	*s = "abcdefg";
// 	int		fd;

// 	fd = open("test.pdf", O_RDWR);

// 	ft_putendl_fd(s, fd);
// }