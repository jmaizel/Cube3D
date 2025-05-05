/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:44:42 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/05 14:25:10 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Vérifie si une ligne est une ligne de map valide
 */
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

/**
 * Vérifie si une ligne vide est suivie d'une ligne de map valide
 */
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

/**
 * Compte les lignes de la map et gestion des erreurs
 */
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
			return (exit_error("Error\nLigne vide dans la map"), 0);
	}
	else
	{
		if (*in_map)
			return (0);
	}
	return (1);
}
