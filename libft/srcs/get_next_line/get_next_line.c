/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:01:01 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/06 13:10:21 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	char	*c;
	char	*buffer;

	buffer = malloc(10000);
	c = buffer;
	while (read(fd, c, 1) > 0 && *c++ != '\n')
		;
	if (c > buffer)
	{
		*c = 0;
		return (buffer);
	}
	else
	{
		free(buffer);
		return (NULL);
	}
}
