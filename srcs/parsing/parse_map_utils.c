/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:44:42 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:46:22 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *line)
{
	int	i;
	int	found_valid_char;

	i = 0;
	found_valid_char = 0;
	while (line[i])
	{
		if (ft_strchr("01NSEWDM", line[i]))
			found_valid_char = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (found_valid_char);
}

int	is_map_interrupted(char **lines, int i)
{
	int	j;

	j = i + 1;
	while (lines[j])
	{
		if (is_map_line(lines[j]))
			return (1);
		j++;
	}
	return (0);
}

int	handle_map_line(char **lines, int i, int *in_map, int *map_lines)
{
	if (is_map_line(lines[i]))
	{
		*in_map = 1;
		(*map_lines)++;
		return (1);
	}
	else if (lines[i][0] == '\0')
	{
		if (*in_map && is_map_interrupted(lines, i))
			return (exit_error("Error\nEmpty line in the map"), 0);
	}
	else
	{
		if (*in_map)
			return (0);
	}
	return (1);
}
