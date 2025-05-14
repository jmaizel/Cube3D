/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:41:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/14 10:43:12 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	cleanup_config_resources(t_game *game)
{
	if (!game)
		return ;
	free_main_textures(game);
	free_paths(game);
}
