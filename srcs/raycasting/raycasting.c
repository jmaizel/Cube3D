/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:08:46 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 18:52:49 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Initialise les paramètres du rayon pour un x donné de l'écran
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @param x Coordonnée X sur l'écran
 */
void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->pos_x = game->player.x;
	ray->pos_y = game->player.y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (fabs(ray->dir_x) < 1e-10)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (fabs(ray->dir_y) < 1e-10)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->hit_type = 0;
}

/**
 * Calcule la direction du pas et la distance jusqu'à la prochaine intersection
 * 
 * @param ray Structure contenant les informations du rayon
 */
void	calculate_step_and_side_dist(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

/**
 * Vérifie si une position dans la map est valide
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @return 1 si la position est valide, 0 sinon
 */
static int	is_valid_ray_position(t_ray *ray, t_game *game)
{
	if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0)
		return (0);
	if (ray->map_x >= (int)ft_strlen(game->map.grid[ray->map_y]))
		return (0);
	return (1);
}

/**
 * Vérifie si le rayon a touché un mur ou une porte
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @return 1 si le rayon a touché quelque chose, 0 sinon
 */
static int	is_ray_hit(t_ray *ray, t_game *game)
{
	char	cell;

	if (!is_valid_ray_position(ray, game))
		return (1);
	cell = game->map.grid[ray->map_y][ray->map_x];
	if (cell == '1' || cell == ' ')
		return (1);
	if (cell == 'D')
	{
		ray->hit_type = game->door_opened ? 3 : 2;
		return (1);
	}
	return (0);
}

/**
 * Exécute l'algorithme DDA pour trouver le mur touché
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 */
void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_ray_hit(ray, game))
			ray->hit = 1;
	}
}

/**
 * Calcule la hauteur de la ligne à dessiner à l'écran
 * 
 * @param ray Structure contenant les informations du rayon
 */
void	calculate_line_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/**
 * Fonction principale de raycasting pour toute la largeur de l'écran
 * 
 * @param game Structure principale du jeu
 */
void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray);
		perform_dda(&ray, game);
		calculate_line_height(&ray);
		draw_textured_line(x, &ray, game);
		x++;
	}
}
