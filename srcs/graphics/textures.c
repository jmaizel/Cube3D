/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 18:00:10 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Détermine quelle texture utiliser selon le côté du mur touché
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @param tex Pointeur sur pointeur pour stocker la texture sélectionnée
 */
void	get_texture(t_ray *ray, t_game *game, t_texture **tex)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			*tex = &game->east_tex;
		else
			*tex = &game->west_tex;
	}
	else
	{
		if (ray->dir_y > 0)
			*tex = &game->south_tex;
		else
			*tex = &game->north_tex;
	}
}

/**
 * Calcule la coordonnée X de la texture pour le mur touché
 * 
 * @param ray Structure contenant les informations du rayon
 * @param wall_x Pointeur pour stocker la position exacte du point de collision
 * @param tex_x Pointeur pour stocker la coordonnée X de la texture
 * @param tex Texture à utiliser
 */
void	calculate_texture_x(t_ray *ray, double *wall_x, int *tex_x,
		t_texture *tex)
{
	if (ray->side == 0)
		*wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		*wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		*tex_x = tex->width - *tex_x - 1;
}

/**
 * Charge une texture depuis un fichier XPM
 * 
 * @param game Structure principale du jeu
 * @param texture Structure pour stocker la texture chargée
 * @param path Chemin vers le fichier XPM
 * @return 1 si le chargement a réussi, 0 sinon
 */
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

/**
 * Charge toutes les textures nécessaires au jeu
 * 
 * @param game Structure principale du jeu
 * @return 1 si toutes les textures ont été chargées, 0 sinon
 */
int	load_all_textures(t_game *game)
{
	int	i;

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
	t_texture	*tex;
	t_tex_params	params;
	int			y;
	int			tex_y;
	int			color;

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
			color = apply_transparency(color);
		game->img_data[y * (game->size_line / 4) + x] = color;
		y++;
	}
}
