/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:39:40 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 15:42:49 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DR ", 3) == 0 || ft_strncmp(line, "MT", 2) == 0
		|| ft_strncmp(line, "WP", 2) == 0);
}

int	validate_required_configs(t_config_flags *flags)
{
	if (!flags->no_set)
		return (exit_error("Error\nMissing NO texture"), 0);
	if (!flags->so_set)
		return (exit_error("Error\nMissing SO texture"), 0);
	if (!flags->we_set)
		return (exit_error("Error\nMissing WE texture"), 0);
	if (!flags->ea_set)
		return (exit_error("Error\nMissing EA texture"), 0);
	if (!flags->f_set)
		return (exit_error("Error\nMissing F color"), 0);
	if (!flags->c_set)
		return (exit_error("Error\nMissing C color"), 0);
	return (1);
}
