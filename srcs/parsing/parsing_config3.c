/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:32:17 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/05 15:07:10 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initialise la structure de données de config
 */
static void	init_config_data(t_config_data *data, t_game *game,
		int *config_count, t_config_flags *flags)
{
	data->game = game;
	data->config_count = config_count;
	data->flags = flags;
	data->phase = 0;
}

/**
 * Initialise les paramètres pour le parsing
 */
static void	init_parse_params(int *i, int *config_count, t_config_flags *flags)
{
	*i = 0;
	*config_count = 0;
	ft_memset(flags, 0, sizeof(t_config_flags));
}

/**
 * Traite les résultats de la configuration
 */
static int	handle_config_result(char **lines, t_config_data *data,
		int *map_start_index, int i, int result)
{
	(void)lines;
	if (result < 0)
		return (0);
	if (result == 2 || data->phase == 2)
	{
		*map_start_index = i;
		return (2);
	}
	return (1);
}

/**
 * Traite les lignes pour le parsing
 */
static int	process_config_lines(char **lines, t_game *game,
		int *map_start_index, t_config_flags *flags)
{
	int				i;
	int				config_count;
	int				result;
	t_config_data	data;

	init_parse_params(&i, &config_count, flags);
	init_config_data(&data, game, &config_count, flags);
	while (lines[i])
	{
		if (lines[i][0] != '\0')
		{
			result = handle_config(&data, lines[i]);
			result = handle_config_result(lines, &data, map_start_index, i,
					result);
			if (result == 0 || result == 2)
				break ;
		}
		i++;
	}
	return (check_config_count(config_count, 6,
			"Error\nConfiguration incomplète"));
}

/**
 * Parse les configurations du fichier .cub
 */
int	parse_config(char **lines, t_game *game, int *map_start_index)
{
	t_config_flags	flags;

	return (process_config_lines(lines, game, map_start_index, &flags));
}
