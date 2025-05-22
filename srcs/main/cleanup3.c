/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:00:41 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/22 13:25:42 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


/* Dans cleanup3.c, remplacez la fonction cleanup_wall_textures par : */

static void	cleanup_wall_textures(t_game *game)
{
	if (game->north_tex.img)
	{
		if (game->mlx && game->north_tex.data)
			mlx_destroy_image(game->mlx, game->north_tex.img);
		else if (!game->mlx)
			free(game->north_tex.img);
		game->north_tex.img = NULL;
	}
	if (game->south_tex.img)
	{
		if (game->mlx && game->south_tex.data)
			mlx_destroy_image(game->mlx, game->south_tex.img);
		else if (!game->mlx)
			free(game->south_tex.img);
		game->south_tex.img = NULL;
	}
	if (game->east_tex.img)
	{
		if (game->mlx && game->east_tex.data)
			mlx_destroy_image(game->mlx, game->east_tex.img);
		else if (!game->mlx)
			free(game->east_tex.img);
		game->east_tex.img = NULL;
	}
	if (game->west_tex.img)
	{
		if (game->mlx && game->west_tex.data)
			mlx_destroy_image(game->mlx, game->west_tex.img);
		else if (!game->mlx)
			free(game->west_tex.img);
		game->west_tex.img = NULL;
	}
	if (game->door_tex.img)
	{
		if (game->mlx && game->door_tex.data)
			mlx_destroy_image(game->mlx, game->door_tex.img);
		else if (!game->mlx)
			free(game->door_tex.img);
		game->door_tex.img = NULL;
	}
}

/* Remplacez également cleanup_weapon_textures par : */

static void	cleanup_weapon_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->weapon_frames[i].img)
		{
			if (game->mlx && game->weapon_frames[i].data)
				mlx_destroy_image(game->mlx, game->weapon_frames[i].img);
			game->weapon_frames[i].img = NULL;
		}
		if (game->weapon_paths[i])
		{
			free(game->weapon_paths[i]);
			game->weapon_paths[i] = NULL;
		}
		i++;
	}
}

/* Et cleanup_monster_textures par : */

static void	cleanup_monster_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->monster_frames[i].img)
		{
			if (game->mlx && game->monster_frames[i].data)
				mlx_destroy_image(game->mlx, game->monster_frames[i].img);
			game->monster_frames[i].img = NULL;
		}
		if (game->monster_paths[i])
		{
			free(game->monster_paths[i]);
			game->monster_paths[i] = NULL;
		}
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
