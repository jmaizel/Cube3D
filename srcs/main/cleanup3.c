/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:00:41 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/19 17:40:16 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	cleanup_wall_textures(t_game *game)
{
	if (game->north_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->north_tex.img);
	else if (game->north_tex.img)
		free(game->north_tex.img);
	if (game->south_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->south_tex.img);
	else if (game->south_tex.img)
		free(game->south_tex.img);
	if (game->east_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->east_tex.img);
	else if (game->east_tex.img)
		free(game->east_tex.img);
	if (game->west_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->west_tex.img);
	else if (game->west_tex.img)
		free(game->west_tex.img);
	if (game->door_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->door_tex.img);
	else if (game->door_tex.img)
		free(game->door_tex.img);
}

static void	cleanup_weapon_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_frames[i].img && game->mlx)
			mlx_destroy_image(game->mlx, game->weapon_frames[i].img);
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
}

static void	cleanup_monster_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_frames[i].img && game->mlx)
			mlx_destroy_image(game->mlx, game->monster_frames[i].img);
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
		i++;
	}
}

void	cleanup_texture_resources(t_game *game)
{
	if (!game)
		return ;
	cleanup_wall_textures(game);
	cleanup_weapon_textures(game);
	cleanup_monster_textures(game);
	if (game->victory_tex.img && game->mlx)
		mlx_destroy_image(game->mlx, game->victory_tex.img);
}
