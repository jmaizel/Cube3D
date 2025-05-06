/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/06 11:37:40 by jmaizel          ###   ########.fr       */
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
	char	*original_path;

	while (*path && (*path == ' ' || *path == '\t'))
		path++;
	original_path = (char *)texture->img;
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (exit_error("Erreur: Impossible de charger la texture"), 0);
	if (original_path)
		free(original_path);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (1);
}
