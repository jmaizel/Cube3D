/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:50:20 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/01 19:38:02 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Applique un effet d'assombrissement aux murs côté Y
 *
 * @param color Couleur d'origine
 * @return Couleur assombrie
 */
int	apply_side_shading(int color)
{
	return ((color >> 1) & 0x7F7F7F);
}

/**
 * Applique un effet de transparence pour les portes ouvertes
 *
 * @param color Couleur d'origine
 * @return Couleur semi-transparente
 */
int	apply_transparency(int color)
{
	int	alpha;
	int	red;
	int	green;
	int	blue;

	alpha = 153;
	red = ((color >> 16) & 0xFF) * alpha / 255;
	green = ((color >> 8) & 0xFF) * alpha / 255;
	blue = (color & 0xFF) * alpha / 255;
	return ((red << 16) | (green << 8) | blue);
}

/**
 * Libère la mémoire des chemins de textures des murs
 *
 * @param game Structure principale du jeu
 */
static void	free_wall_paths(t_game *game)
{
	if (game->south_tex.img)
		free(game->south_tex.img);
	if (game->north_tex.img)
		free(game->north_tex.img);
	if (game->east_tex.img)
		free(game->east_tex.img);
	if (game->west_tex.img)
		free(game->west_tex.img);
	if (game->door_tex.img)
		free(game->door_tex.img);
}

/**
 * Libère la mémoire des chemins de textures des armes et monstres
 *
 * @param game Structure principale du jeu
 */
static void	free_sprites_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
		i++;
	}
}

/**
 * Libère la mémoire des chemins de textures après leur chargement
 *
 * @param game Structure principale du jeu
 */
void	free_texture_paths(t_game *game)
{
	free_wall_paths(game);
	free_sprites_paths(game);
}
