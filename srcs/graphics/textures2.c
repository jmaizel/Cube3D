/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:30:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/03 14:14:27 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Charge les textures des murs
 * 
 * @param game Structure principale du jeu
 * @return 1 si réussi, 0 sinon
 */
static int	load_wall_textures(t_game *game)
{
	if (!load_texture(game, &game->north_tex, (char *)game->north_tex.img))
		return (0);
	if (!load_texture(game, &game->south_tex, (char *)game->south_tex.img))
		return (0);
	if (!load_texture(game, &game->east_tex, (char *)game->east_tex.img))
		return (0);
	if (!load_texture(game, &game->west_tex, (char *)game->west_tex.img))
		return (0);
	if (game->door_tex.img && !load_texture(game, &game->door_tex,
			(char *)game->door_tex.img))
		return (0);
	return (1);
}

/**
 * Charge les textures des armes
 * 
 * @param game Structure principale du jeu
 * @return 1 si réussi, 0 sinon
 */
static int	load_weapon_textures(t_game *game)
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
	return (1);
}

/**
 * Charge les textures des monstres
 * 
 * @param game Structure principale du jeu
 * @return 1 si réussi, 0 sinon
 */
static int	load_monster_textures(t_game *game)
{
	int	i;

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

/**
 * Charge toutes les textures nécessaires au jeu
 * 
 * @param game Structure principale du jeu
 * @return 1 si toutes les textures ont été chargées, 0 sinon
 */
int	load_all_textures(t_game *game)
{
	if (!load_wall_textures(game))
		return (0);
	if (!load_weapon_textures(game))
		return (0);
	if (!load_monster_textures(game))
		return (0);
	free_texture_paths(game);
	return (1);
}

/**
 * Calcule et dessine une colonne de pixel texturée pour un mur
 * 
 * @param x Coordonnée X de la colonne à dessiner
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 */
void	draw_textured_line(int x, t_ray *ray, t_game *game)
{
	t_texture		*tex;
	t_tex_params	params;
	int				y;
	int				tex_y;
	int				color;

	if (ray->hit_type == 2 || ray->hit_type == 3)
		tex = &game->door_tex;
	else
		get_texture(ray, game, &tex);
	prepare_texture_params(ray, tex, &params);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)params.tex_pos & (tex->height - 1);
		params.tex_pos += params.step;
		color = tex->data[tex_y * tex->width + params.tex_x];
		if (ray->side == 1 && ray->hit_type < 2)
			color = apply_side_shading(color);
		if (ray->hit_type == 3)
			color = change_door_color(color);
		game->img_data[y * (game->size_line / 4) + x] = color;
		y++;
	}
}
