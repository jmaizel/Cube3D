/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:08:46 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 09:25:13 by cdedessu         ###   ########.fr       */
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
 * Configure le type de hit pour les portes
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 */
static void	set_door_hit_type(t_ray *ray, t_game *game)
{
	ray->hit = 1;
	if (game->door_opened)
		ray->hit_type = 3;
	else
		ray->hit_type = 2;
}

/**
 * Vérifie si le rayon a touché un mur ou une porte
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @return 1 si le rayon a touché quelque chose, 0 sinon
 */
int	is_ray_hit(t_ray *ray, t_game *game)
{
	char	cell;

	if (!is_valid_ray_position(ray, game))
		return (1);
	cell = game->map.grid[ray->map_y][ray->map_x];
	if (cell == '1' || cell == ' ')
		return (1);
	if (cell == 'D')
	{
		set_door_hit_type(ray, game);
		return (1);
	}
	return (0);
}
