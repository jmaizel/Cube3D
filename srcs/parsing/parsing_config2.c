/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:32:17 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:50:05 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

static int	determine_phase(int current_phase, char *line)
{
	if (current_phase == 0 && is_color_line(line))
		return (1);
	else if (current_phase <= 1 && is_map_start(line))
		return (2);
	return (current_phase);
}

static int	check_element_order(int phase, char *line)
{
	if (phase == 1 && is_texture_line(line))
		return (exit_error("Error\nTextures error order declaration"),
			0);
	return (1);
}

static int	prepare_phase(char *line, int *phase)
{
	*phase = determine_phase(*phase, line);
	if (!check_element_order(*phase, line))
		return (-1);
	if (*phase == 2)
		return (1);
	return (0);
}

int	handle_config(t_config_data *data, char *line)
{
	int	result;
	int	prep;

	prep = prepare_phase(line, &data->phase);
	if (prep < 0)
		return (-1);
	if (prep > 0)
		return (2);
	result = process_line(line, data->game, data->config_count, data->flags);
	return (result);
}
