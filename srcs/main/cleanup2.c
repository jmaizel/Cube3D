/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clanup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:41:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/13 16:41:54 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Nettoie les textures principales
 */
static void	free_main_textures(t_game *game)
{
	if (!game->mlx)
	{
		if (game->north_tex.img)
			free(game->north_tex.img);
		if (game->south_tex.img)
			free(game->south_tex.img);
		if (game->east_tex.img)
			free(game->east_tex.img);
		if (game->west_tex.img)
			free(game->west_tex.img);
		if (game->door_tex.img)
			free(game->door_tex.img);
	}
}

/**
 * Nettoie les chemins d'armes et de monstres
 */
static void	free_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
		i++;
	}
}

/**
 * Nettoie les ressources allouées pendant la phase de configuration
 */
void	cleanup_config_resources(t_game *game)
{
	if (!game)
		return ;
	free_main_textures(game);
	free_paths(game);
}
