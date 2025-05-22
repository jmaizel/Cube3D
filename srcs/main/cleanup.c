/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:41:47 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 11:31:49 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	exit(0);
	return (0);
}
