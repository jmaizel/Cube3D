/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:22:34 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 16:04:16 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Détermine la texture à utiliser selon le côté touché
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

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->north_tex, (char *)game->north_tex.img))
		return (0);
	if (!load_texture(game, &game->south_tex, (char *)game->south_tex.img))
		return (0);
	if (!load_texture(game, &game->east_tex, (char *)game->east_tex.img))
		return (0);
	if (!load_texture(game, &game->west_tex, (char *)game->west_tex.img))
		return (0);
	if (!load_texture(game, &game->door_tex, game->door_path))
		return (0);
	if (!load_texture(game, &game->weapon_tex, game->weapon_path))
		return (0);
	free(game->weapon_path);
	free(game->door_path); // libère une fois chargé
	free(game->south_tex.img);
	free(game->north_tex.img);
	free(game->east_tex.img);
	free(game->west_tex.img);
	return (1);
}
void	draw_textured_line(int x, t_ray *ray, t_game *game)
{
	t_texture	*tex;
	double		wall_x;
	int			color;
	int			y;

	int tex_x, tex_y;
	double step, tex_pos;
	if (ray->hit_type == 2)
		tex = &game->door_tex;
	else
		get_texture(ray, game, &tex);
	calculate_texture_x(ray, &wall_x, &tex_x, tex);
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = tex->data[tex_y * tex->width + tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		game->img_data[y * (game->size_line / 4) + x] = color;
		y++;
	}
}
