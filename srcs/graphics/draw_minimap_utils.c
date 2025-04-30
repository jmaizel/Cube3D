/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:46:10 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/01 13:46:15 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine une ligne entre deux points (algorithme de Bresenham)
 * 
 * @param game Structure principale du jeu
 * @param x0 Coordonnée X du premier point
 * @param y0 Coordonnée Y du premier point
 * @param x1 Coordonnée X du second point
 * @param y1 Coordonnée Y du second point
 * @param color Couleur de la ligne
 */
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && y0 >= 0 && x0 < WIN_WIDTH && y0 < WIN_HEIGHT)
			game->img_data[y0 * (game->size_line / 4) + x0] = color;
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

/**
 * Dessine la bordure horizontale de la minimap
 * 
 * @param game Structure principale du jeu
 * @param x Position X de la minimap
 * @param y Position Y de la minimap
 * @param width Largeur de la minimap
 * @param border_size Épaisseur de la bordure
 * @param border_color Couleur de la bordure
 */
static void	draw_horizontal_borders(t_game *game, int x, int y,
		int width, int border_size, int border_color)
{
	int	i;
	int	j;
	int	height;

	height = game->map.height * 7;
	i = -border_size;
	while (i < width + border_size)
	{
		j = -border_size;
		while (j < 0)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			j++;
		}
		j = height;
		while (j < height + border_size)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			j++;
		}
		i++;
	}
}

/**
 * Dessine la bordure verticale de la minimap
 * 
 * @param game Structure principale du jeu
 * @param x Position X de la minimap
 * @param y Position Y de la minimap
 * @param height Hauteur de la minimap
 * @param border_size Épaisseur de la bordure
 * @param border_color Couleur de la bordure
 */
static void	draw_vertical_borders(t_game *game, int x, int y,
		int height, int border_size, int border_color)
{
	int	i;
	int	j;
	int	width;

	width = game->map.width * 7;
	j = -border_size;
	while (j < height + border_size)
	{
		i = -border_size;
		while (i < 0)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			i++;
		}
		i = width;
		while (i < width + border_size)
		{
			if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT
				&& x + i < WIN_WIDTH)
				game->img_data[(y + j) * (game->size_line / 4)
					+ (x + i)] = border_color;
			i++;
		}
		j++;
	}
}

/**
 * Dessine un cadre autour de la minimap
 * 
 * @param game Structure principale du jeu
 * @param x Position X de la minimap
 * @param y Position Y de la minimap
 * @param width Largeur de la minimap
 * @param height Hauteur de la minimap
 */
void	draw_minimap_border(t_game *game, int x, int y, int width, int height)
{
	int	border_size;
	int	border_color;

	border_size = 2;
	border_color = MAP_BORDER_COLOR;
	draw_horizontal_borders(game, x, y, width, border_size, border_color);
	draw_vertical_borders(game, x, y, height, border_size, border_color);
}
