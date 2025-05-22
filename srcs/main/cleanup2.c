/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:41:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 13:33:25 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_main_textures(t_game *game)
{
	if (game->north_tex.img)
	{
		free(game->north_tex.img);
		game->north_tex.img = NULL;
	}
	if (game->south_tex.img)
	{
		free(game->south_tex.img);
		game->south_tex.img = NULL;
	}
	if (game->east_tex.img)
	{
		free(game->east_tex.img);
		game->east_tex.img = NULL;
	}
	if (game->west_tex.img)
	{
		free(game->west_tex.img);
		game->west_tex.img = NULL;
	}
	if (game->door_tex.img)
	{
		free(game->door_tex.img);
		game->door_tex.img = NULL;
	}
}

static void	free_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->weapon_paths[i])
		{
			free(game->weapon_paths[i]);
			game->weapon_paths[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (game->monster_paths[i])
		{
			free(game->monster_paths[i]);
			game->monster_paths[i] = NULL;
		}
		i++;
	}
}

void	cleanup_config_resources(t_game *game)
{
	if (!game)
		return ;
	free_main_textures(game);
	free_paths(game);
}
