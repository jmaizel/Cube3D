/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:00:41 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/22 14:55:28 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_cleanup_single_texture(t_game *game, t_texture *tex)
{
	if (tex->img)
	{
		if (game->mlx && tex->data)
			mlx_destroy_image(game->mlx, tex->img);
		else if ((char *)tex->img)
			free((char *)tex->img);
		tex->img = NULL;
		tex->data = NULL;
	}
}

static void	cleanup_wall_textures(t_game *game)
{
	ft_cleanup_single_texture(game, &game->north_tex);
	ft_cleanup_single_texture(game, &game->south_tex);
	ft_cleanup_single_texture(game, &game->east_tex);
	ft_cleanup_single_texture(game, &game->west_tex);
	ft_cleanup_single_texture(game, &game->door_tex);
}

static void	cleanup_weapon_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_cleanup_single_texture(game, &game->weapon_frames[i]);
		if (game->weapon_paths[i])
		{
			free(game->weapon_paths[i]);
			game->weapon_paths[i] = NULL;
		}
		i++;
	}
}

static void	cleanup_monster_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_cleanup_single_texture(game, &game->monster_frames[i]);
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
	ft_cleanup_single_texture(game, &game->victory_tex);
}
