/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:00:00 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 14:34:31 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Lance un rayon pour chaque colonne de l'écran */
void complete_raycasting(t_game *game)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        ft_memset(&ray, 0, sizeof(t_ray));
        init_ray(&ray, game, x);
        calculate_step_and_side_dist(&ray);
        safe_perform_dda(&ray, game);
        calculate_line_height(&ray);
        game->z_buffer[x] = ray.perp_wall_dist; // Stocke la distance pour les sprites
        draw_textured_line(x, &ray, game);
        x++;
    }
}

/* Version sécurisée du DDA avec gestion des portes */
void safe_perform_dda(t_ray *ray, t_game *game)
{
    int max_iterations;
    int iterations;

    max_iterations = 100;
    iterations = 0;
    while (ray->hit == 0 && iterations < max_iterations)
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

        // Vérifications des limites et des murs
        if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0)
        {
            ray->hit = 1;
        }
        else if (ray->map_x >= (int)ft_strlen(game->map.grid[ray->map_y]))
        {
            ray->hit = 1;
        }
        else if (game->map.grid[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
        }
        else if (game->map.grid[ray->map_y][ray->map_x] == 'D')
        {
            ray->hit = 1;
            if (game->door_opened)
                ray->hit_type = 3; // Porte ouverte (semi-transparente)
            else
                ray->hit_type = 2; // Porte fermée 
        }
        iterations++;
    }
}

/* Version de test qui dessine des lignes colorées sans textures */
void safe_draw_textured_line(int x, t_ray *ray, t_game *game)
{
    int color;
    int y;

    color = 0;
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            color = 0xFF0000;
        else
            color = 0x00FF00;
    }
    else
    {
        if (ray->dir_y > 0)
            color = 0x0000FF;
        else
            color = 0xFFFF00;
    }
    if (ray->side == 1)
        color = (color >> 1) & 0x7F7F7F;
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        if (y >= 0 && y < WIN_HEIGHT && x >= 0 && x < WIN_WIDTH)
            game->img_data[y * (game->size_line / 4) + x] = color;
        y++;
    }
}