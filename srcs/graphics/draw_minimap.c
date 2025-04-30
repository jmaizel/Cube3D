/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 19:07:18 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine le fond de la minimap
 * 
 * @param game Structure principale du jeu
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 * @param map_size Structure contenant les dimensions de la minimap
 */
static void	draw_minimap_background(t_game *game, int offset_x, int offset_y,
		t_minimap_size map_size)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_size.height)
	{
		x = 0;
		while (x < map_size.width)
		{
			if (offset_y + y < WIN_HEIGHT && offset_x + x < WIN_WIDTH)
				game->img_data[(offset_y + y) * (game->size_line / 4)
					+ (offset_x + x)] = MAP_BG_COLOR;
			x++;
		}
		y++;
	}
}

/**
 * Dessine les cases (murs et sol) sur la minimap
 * 
 * @param game Structure principale du jeu
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 * @param cell_size Taille en pixels de chaque case
 */
static void	draw_map_cells(t_game *game, int offset_x, int offset_y,
		int cell_size)
{
	int	map_y;
	int	map_x;
	int	pixel_x;
	int	pixel_y;
	int	color;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map.grid[map_y]))
		{
			pixel_x = offset_x + map_x * cell_size;
			pixel_y = offset_y + map_y * cell_size;
			if (game->map.grid[map_y][map_x] == '1')
				color = MAP_WALL_COLOR;
			else if (game->map.grid[map_y][map_x] == '0'
					|| ft_strchr("NSEWDMP", game->map.grid[map_y][map_x]))
				color = MAP_FLOOR_COLOR;
			else
			{
				map_x++;
				continue ;
			}
			draw_cell(game, pixel_x, pixel_y, cell_size, color);
			map_x++;
		}
		map_y++;
	}
}

/**
 * Dessine le joueur sur la minimap
 * 
 * @param game Structure principale du jeu
 * @param offset_x Position X de la minimap
 * @param offset_y Position Y de la minimap
 * @param cell_size Taille en pixels de chaque case
 */
static void	draw_player(t_game *game, int offset_x, int offset_y,
		int cell_size)
{
	int	player_x;
	int	player_y;
	int	dir_x;
	int	dir_y;

	player_x = offset_x + (int)(game->player.x * cell_size);
	player_y = offset_y + (int)(game->player.y * cell_size);
	draw_player_dot(game, player_x, player_y, MAP_PLAYER_COLOR);
	dir_x = player_x + (int)(game->player.dir_x * cell_size * 2);
	dir_y = player_y + (int)(game->player.dir_y * cell_size * 2);
	draw_line(game, player_x, player_y, dir_x, dir_y, MAP_PLAYER_COLOR);
}

/**
 * Calcule les dimensions de la minimap
 * 
 * @param game Structure principale du jeu
 * @param cell_size Taille en pixels de chaque case
 * @return Structure contenant les dimensions de la minimap
 */
static t_minimap_size	calculate_minimap_size(t_game *game, int *cell_size)
{
	t_minimap_size	size;
	int				max_width;

	size.width = game->map.width * (*cell_size);
	size.height = game->map.height * (*cell_size);
	max_width = WIN_WIDTH / 4;
	if (size.width > max_width)
	{
		*cell_size = max_width / game->map.width;
		size.width = game->map.width * (*cell_size);
		size.height = game->map.height * (*cell_size);
	}
	return (size);
}

/**
 * Dessine la minimap en haut à gauche de l'écran
 * 
 * @param game Structure principale du jeu
 */
void	draw_minimap(t_game *game)
{
	int				cell_size;
	int				offset_x;
	int				offset_y;
	t_minimap_size	map_size;

	cell_size = 6;
	offset_x = 20;
	offset_y = 20;
	map_size = calculate_minimap_size(game, &cell_size);
	draw_minimap_background(game, offset_x, offset_y, map_size);
	draw_map_cells(game, offset_x, offset_y, cell_size);
	draw_player(game, offset_x, offset_y, cell_size);
	draw_minimap_border(game, offset_x, offset_y, map_size.width,
		map_size.height);
}
