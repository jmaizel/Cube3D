/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:20:26 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Charge une texture depuis un fichier */
int	load_texture(t_game *game, t_texture *texture, char *path)
{
	while (*path && (*path == ' ' || *path == '\t'))
		path++;
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (exit_error("Erreur: Impossible de charger la texture"), 0);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (1);
}

/* Charge les textures obligatoires (Nord, Sud, Est, Ouest) */
void	load_base_textures(t_game *game)
{
	if (!load_texture(game, &game->north_tex, (char *)game->north_tex.img))
		return ;
	if (!load_texture(game, &game->south_tex, (char *)game->south_tex.img))
		return ;
	if (!load_texture(game, &game->east_tex, (char *)game->east_tex.img))
		return ;
	if (!load_texture(game, &game->west_tex, (char *)game->west_tex.img))
		return ;
}

/* Charge les frames d'animation pour l'arme et les monstres */
int	load_animation_frames(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_paths[i] && !load_texture(game,
				&game->weapon_frames[i], game->weapon_paths[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_paths[i] && !load_texture(game,
				&game->monster_frames[i], game->monster_paths[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Libère la mémoire utilisée par les textures */
void	free_textures_memory(t_game *game)
{
	int	i;

	if (game->south_tex.img)
		free(game->south_tex.img);
	if (game->north_tex.img)
		free(game->north_tex.img);
	if (game->east_tex.img)
		free(game->east_tex.img);
	if (game->west_tex.img)
		free(game->west_tex.img);
	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_paths[i])
			free(game->weapon_paths[i]);
		i++;
	}
	if (game->door_tex.img)
		free(game->door_tex.img);
	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_paths[i])
			free(game->monster_paths[i]);
		i++;
	}
}

/* Charge toutes les textures du jeu */
int	load_all_textures(t_game *game)
{
	load_base_textures(game);
	if (game->door_tex.img && !load_texture(game, &game->door_tex,
			(char *)game->door_tex.img))
		return (0);
	if (!load_animation_frames(game))
		return (0);
	free_textures_memory(game);
	return (1);
}