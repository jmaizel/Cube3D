/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:41:47 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/06 12:10:34 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Nettoie les ressources allouées pendant la phase de configuration
 */
void	cleanup_config_resources(t_game *game)
{
	int	i;

	if (game->north_tex.img && !game->mlx)
		free(game->north_tex.img);
	if (game->south_tex.img && !game->mlx)
		free(game->south_tex.img);
	if (game->east_tex.img && !game->mlx)
		free(game->east_tex.img);
	if (game->west_tex.img && !game->mlx)
		free(game->west_tex.img);
	if (game->door_tex.img && !game->mlx)
		free(game->door_tex.img);
	i = 0;
	while (i < 4)
	{
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
	i = 0;
	while (i++ < 4)
	{
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
	}
}

/**
 * Libère les textures des murs
 */
static void	free_wall_textures(t_game *game)
{
	if (game->north_tex.img)
		mlx_destroy_image(game->mlx, game->north_tex.img);
	if (game->south_tex.img)
		mlx_destroy_image(game->mlx, game->south_tex.img);
	if (game->east_tex.img)
		mlx_destroy_image(game->mlx, game->east_tex.img);
	if (game->west_tex.img)
		mlx_destroy_image(game->mlx, game->west_tex.img);
	if (game->door_tex.img)
		mlx_destroy_image(game->mlx, game->door_tex.img);
}

/**
 * Libère les textures des armes
 */
static void	free_weapon_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_frames[i].img)
			mlx_destroy_image(game->mlx, game->weapon_frames[i].img);
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
}

/**
 * Libère les textures des monstres
 */
static void	free_monster_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_frames[i].img)
			mlx_destroy_image(game->mlx, game->monster_frames[i].img);
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
		i++;
	}
}

/**
 * Ferme la fenêtre et libère toutes les ressources allouées
 *
 * @param game Structure principale du jeu
 * @return 0 (toujours)
 */
int	close_window(t_game *game)
{
	free_wall_textures(game);
	free_weapon_textures(game);
	free_monster_textures(game);
	if (game->victory_tex.img)
		mlx_destroy_image(game->mlx, game->victory_tex.img);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game->map.grid);
	dummy = get_next_line(-1);
	exit(0);
	return (0);
}
