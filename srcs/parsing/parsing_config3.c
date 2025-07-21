/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:32:17 by jmaizel           #+#    #+#             */
/*   Updated: 2025/06/02 11:44:45 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_config_data(t_config_data *data, t_game *game,
		int *config_count, t_config_flags *flags)
{
	data->game = game;
	data->config_count = config_count;
	data->flags = flags;
	data->phase = 0;
}

static void	init_parse_params(int *i, int *config_count, t_config_flags *flags)
{
	*i = 0;
	*config_count = 0;
	ft_memset(flags, 0, sizeof(t_config_flags));
}

static int	handle_config_result(t_config_data *data, int *map_start_index,
		int i, int result)
{
	if (result < 0)
		return (0);
	if (result == 2 || data->phase == 2)
	{
		*map_start_index = i;
		return (2);
	}
	return (1);
}

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
			result = handle_config_result(&data, map_start_index, i, result);
			if (result == 0)
				return (0);
			if (result == 2)
				break ;
		}
		i++;
	}
	if (!check_config_count(config_count, 6, "Error\nIncomplete configuration"))
		return (0);
	return (validate_required_configs(flags));
}

int	parse_config(char **lines, t_game *game, int *map_start_index)
{
	t_config_flags	flags;

	return (process_config_lines(lines, game, map_start_index, &flags));
}
