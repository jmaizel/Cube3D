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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:05:30 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/01 18:05:33 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Dessine une ligne entre deux points (algorithme de Bresenham)
 * 
 * @param game Structure principale du jeu
 * @param x0 Coordonnée X du point de départ
 * @param y0 Coordonnée Y du point de départ
 * @param x1 Coordonnée X du point d'arrivée
 * @param y1 Coordonnée Y du point d'arrivée
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
 * Dessine une cellule de la minimap
 * 
 * @param game Structure principale du jeu
 * @param x Position X de la cellule
 * @param y Position Y de la cellule
 * @param size Taille de la cellule
 * @param color Couleur de la cellule
 */
void	draw_cell(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < size - 1)
	{
		j = 1;
		while (j < size - 1)
		{
			if (y + i < WIN_HEIGHT && x + j < WIN_WIDTH)
				game->img_data[(y + i) * (game->size_line / 4)
					+ (x + j)] = color;
			j++;
		}
		i++;
	}
}

/**
 * Dessine un point représentant le joueur
 * 
 * @param game Structure principale du jeu
 * @param x Position X du joueur
 * @param y Position Y du joueur
 * @param color Couleur du joueur
 */
void	draw_player_dot(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
			{
				if (y + i >= 0 && y + i < WIN_HEIGHT && x + j >= 0
					&& x + j < WIN_WIDTH)
					game->img_data[(y + i) * (game->size_line / 4)
						+ (x + j)] = color;
			}
			j++;
		}
		i++;
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
	int	i;
	int	border_size;
	int	color;

	border_size = 1;
	color = MAP_BORDER_COLOR;
	// Bordures horizontales
	i = -border_size;
	while (i < width + border_size)
	{
		if (y - border_size >= 0 && x + i >= 0 && y - border_size < WIN_HEIGHT
			&& x + i < WIN_WIDTH)
			game->img_data[(y - border_size) * (game->size_line / 4)
				+ (x + i)] = color;
		if (y + height >= 0 && x + i >= 0 && y + height < WIN_HEIGHT
			&& x + i < WIN_WIDTH)
			game->img_data[(y + height) * (game->size_line / 4)
				+ (x + i)] = color;
		i++;
	}
	// Bordures verticales
	i = -border_size;
	while (i < height + border_size)
	{
		if (y + i >= 0 && x - border_size >= 0 && y + i < WIN_HEIGHT
			&& x - border_size < WIN_WIDTH)
			game->img_data[(y + i) * (game->size_line / 4)
				+ (x - border_size)] = color;
		if (y + i >= 0 && x + width >= 0 && y + i < WIN_HEIGHT
			&& x + width < WIN_WIDTH)
			game->img_data[(y + i) * (game->size_line / 4)
				+ (x + width)] = color;
		i++;
	}
}
