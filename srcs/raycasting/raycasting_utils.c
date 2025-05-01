/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/01 09:21:15 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Vérifie si le rayon a touché une limite ou un mur
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @return 1 si le rayon a touché, 0 sinon
 */
static int	check_ray_hit_wall(t_ray *ray, t_game *game)
{
	if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0)
		return (1);
	else if (ray->map_x >= (int)ft_strlen(game->map.grid[ray->map_y]))
		return (1);
	else if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

/**
 * Vérifie si le rayon a touché une porte
 * 
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 * @return 1 si le rayon a touché une porte, 0 sinon
 */
static int	check_ray_hit_door(t_ray *ray, t_game *game)
{
	if (game->map.grid[ray->map_y][ray->map_x] == 'D')
	{
		ray->hit = 1;
		if (game->door_opened)
			ray->hit_type = 3;
		else
			ray->hit_type = 2;
		return (1);
	}
	return (0);
}

/**
 * Avance le rayon d'un pas selon l'algorithme DDA
 * 
 * @param ray Structure contenant les informations du rayon
 */
static void	advance_ray(t_ray *ray)
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
}

/**
 * Version sécurisée du DDA avec gestion des portes
 *
 * @param ray Structure contenant les informations du rayon
 * @param game Structure principale du jeu
 */
void	safe_perform_dda(t_ray *ray, t_game *game)
{
	int	max_iterations;
	int	iterations;

	max_iterations = 100;
	iterations = 0;
	while (ray->hit == 0 && iterations < max_iterations)
	{
		advance_ray(ray);
		if (check_ray_hit_wall(ray, game))
			ray->hit = 1;
		else if (check_ray_hit_door(ray, game))
			ray->hit = 1;
		iterations++;
	}
}

/**
 * Lance un rayon pour chaque colonne de l'écran
 *
 * @param game Structure principale du jeu
 */
void	complete_raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray);
		safe_perform_dda(&ray, game);
		calculate_line_height(&ray);
		game->z_buffer[x] = ray.perp_wall_dist;
		draw_textured_line(x, &ray, game);
		x++;
	}
}
