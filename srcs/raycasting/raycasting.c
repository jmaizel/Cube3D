/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:08:46 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/09 15:06:16 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
fonction qui initialise le rayon :
1. position de la camera dans l espace de l ecran (-1 gauche, 0 au centre,
	1 a droite)
2. direction du rayon
3. position de depart (position du joueur)
4. position intiale sur la carte
5 on calculre la longueur du rayon en foncton de la prochaine ligne x ou y
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

/*
fonction pour caclucler la distance jusqu a la prochaine ligne x ou y
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
/*
execute l algorithme DDQ (digital Differential Analysis)
pour trouver le ;ur touche :
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
		if (ray->map_y < 0 || ray->map_y >= game->map.height || 
		    ray->map_x < 0 || ray->map_x >= (int)ft_strlen(game->map.grid[ray->map_y]) || 
		    game->map.grid[ray->map_y][ray->map_x] == '1' || 
		    game->map.grid[ray->map_y][ray->map_x] == ' ')
			ray->hit = 1;
	}
}

/*
Calcule la hauteur de la ligne à dessiner :
 1. calcule la distance perpendiculaire du mur a la camera
 2. calculre la hauteur de la ligne a dssiner
 3. calcule le pixel le plus bas et le plus haut a remplir
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

/*
voici donc la fonction de raycasting qui va s appliquer colonne par colonne :
1. initialise un nouveau rayon
2. calcule la direction du pas et la distance initiale
3. DDa pour trouver le mur touche
4. cacule la hauteur de la ligne a dessiner
5. dessine la ligne avec texture
*/
void	raycasting(t_game *game)
{
	t_ray ray;
	int x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, game, x);
		calculate_step_and_side_dist(&ray);
		perform_dda(&ray, game);
		calculate_line_height(&ray);
		draw_textured_line(x, &ray, game);
		x++;
	}
}