/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_daw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:23:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 16:20:43 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Détermine quelle texture utiliser selon le côté du mur touché */
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

/* Calcule la coordonnée x de la texture pour le mur touché */
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

/* Applique la couleur de la texture avec gestion de transparence pour les portes */
void	apply_texture_color(t_ray *ray, t_game *game, int x, t_texture *tex,
		int tex_x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = tex->data[tex_y * tex->width + tex_x];
		if (ray->side == 1 && ray->hit_type < 2)
			color = (color >> 1) & 0x7F7F7F;
		if (ray->hit_type == 3)
		{
			int alpha = 153;
			int r = ((color >> 16) & 0xFF) * alpha / 255;
			int g = ((color >> 8) & 0xFF) * alpha / 255;
			int b = (color & 0xFF) * alpha / 255;
			color = (r << 16) | (g << 8) | b;
		}
		game->img_data[y * (game->size_line / 4) + x] = color;
		y++;
	}
}

/* Dessine une ligne texturée à l'écran */
void	draw_textured_line(int x, t_ray *ray, t_game *game)
{
	t_texture	*tex;
	double		wall_x;
	int			tex_x;

	if (ray->hit_type == 2 || ray->hit_type == 3)
		tex = &game->door_tex;
	else
		get_texture(ray, game, &tex);
	calculate_texture_x(ray, &wall_x, &tex_x, tex);
	apply_texture_color(ray, game, x, tex, tex_x);
}