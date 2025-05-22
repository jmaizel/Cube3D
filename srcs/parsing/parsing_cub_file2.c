/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:24 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 15:52:08 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_num(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (-1);
		i++;
	}
	return (num);
}

int	count_char(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	parse_color_line(char *line)
{
	char	**parts;
	int		color;
	int		r;
	int		g;
	int		b;

	if (count_char(line, ',') != 2)
		return (exit_error("Error\nInvalid RGB format"), -1);
	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_split(parts), exit_error("Error\nInvalid color"), -1);
	r = get_num(parts[0]);
	g = get_num(parts[1]);
	b = get_num(parts[2]);
	free_split(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (exit_error("Error\nRGB values out of range"), -1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	check_texture_uniqueness(t_game *game)
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	north = (char *)game->north_tex.img;
	south = (char *)game->south_tex.img;
	east = (char *)game->east_tex.img;
	west = (char *)game->west_tex.img;
	if (!north || !south || !east || !west)
	{
		exit_error("Error\nDirection textures missing");
		return (0);
	}
	if (ft_strncmp(north, south, ft_strlen(north) + 1) == 0 || ft_strncmp(north,
			east, ft_strlen(north) + 1) == 0 || ft_strncmp(north, west,
			ft_strlen(north) + 1) == 0 || ft_strncmp(south, east,
			ft_strlen(south) + 1) == 0 || ft_strncmp(south, west,
			ft_strlen(south) + 1) == 0 || ft_strncmp(east, west, ft_strlen(east)
			+ 1) == 0)
	{
		exit_error("Error\nredirection textures must ne different");
		return (0);
	}
	return (1);
}
