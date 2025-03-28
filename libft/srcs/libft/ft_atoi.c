/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:43:45 by cdedessu          #+#    #+#             */
/*   Updated: 2024/12/24 11:46:03 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	sign = 1;
	res = 0;
	if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1))
			error_exit("Error\n integer value out of range");
	}
	if (str[i] != '\0')
		error_exit("Error\n invalid character");
	return (res * sign);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = "10000000000258";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
	return (0);
}
*/