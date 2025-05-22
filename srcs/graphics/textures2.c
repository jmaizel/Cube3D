/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:30:00 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/22 14:01:55 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	load_weapon_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->weapon_frame_count)
	{
		if (game->weapon_paths[i] && !load_texture(game,
				&game->weapon_frames[i], game->weapon_paths[i]))
			return (0);
		free(game->weapon_paths[i]);
		game->weapon_paths[i] = NULL;
		i++;
	}
	return (1);
}

static int	load_monster_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_frame_count)
	{
		if (game->monster_paths[i] && !load_texture(game,
				&game->monster_frames[i], game->monster_paths[i]))
			return (0);
		free(game->monster_paths[i]);
		game->monster_paths[i] = NULL;
		i++;
	}
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_wall_textures(game))
	{
		cleanup_texture_resources(game);
		return (0);
	}
	if (!load_weapon_textures(game))
	{
		cleanup_texture_resources(game);
		return (0);
	}
	if (!load_monster_textures(game))
	{
		cleanup_texture_resources(game);
		return (0);
	}
	if (!load_texture(game, &game->victory_tex, "./textures/victory.xpm"))
	{
		cleanup_texture_resources(game);
		return (0);
	}
	return (1);
}

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