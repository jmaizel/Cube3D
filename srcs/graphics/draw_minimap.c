/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/28 18:17:43 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MAP_WALL_COLOR 0xE0E0E0    // Gris clair pour les murs
#define MAP_FLOOR_COLOR 0x303030   // Gris foncé pour le sol
#define MAP_PLAYER_COLOR 0xFF2020  // Rouge vif pour le joueur
#define MAP_BORDER_COLOR 0x404040  // Couleur de bordure

// Fonction pour dessiner une ligne (algorithme de Bresenham)
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;
    
    while (1) {
        if (x0 >= 0 && y0 >= 0 && x0 < WIN_WIDTH && y0 < WIN_HEIGHT)
            game->img_data[y0 * (game->size_line / 4) + x0] = color;
        
        if (x0 == x1 && y0 == y1)
            break;
            
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Fonction pour dessiner un cadre autour de la minimap
void draw_minimap_border(t_game *game, int x, int y, int width, int height)
{
    int border_size = 2;
    int border_color = MAP_BORDER_COLOR;
    
    // Dessiner les bords horizontaux
    for (int i = -border_size; i < width + border_size; i++) {
        for (int j = -border_size; j < 0; j++) {
            if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT && x + i < WIN_WIDTH)
                game->img_data[(y + j) * (game->size_line / 4) + (x + i)] = border_color;
        }
        for (int j = height; j < height + border_size; j++) {
            if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT && x + i < WIN_WIDTH)
                game->img_data[(y + j) * (game->size_line / 4) + (x + i)] = border_color;
        }
    }
    
    // Dessiner les bords verticaux
    for (int j = -border_size; j < height + border_size; j++) {
        for (int i = -border_size; i < 0; i++) {
            if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT && x + i < WIN_WIDTH)
                game->img_data[(y + j) * (game->size_line / 4) + (x + i)] = border_color;
        }
        for (int i = width; i < width + border_size; i++) {
            if (y + j >= 0 && x + i >= 0 && y + j < WIN_HEIGHT && x + i < WIN_WIDTH)
                game->img_data[(y + j) * (game->size_line / 4) + (x + i)] = border_color;
        }
    }
}

// Fonction principale de la minimap
void draw_minimap(t_game *game)
{
    int size = 7;              // Taille de chaque case
    int offset_x = 30;         // Position X de la minimap
    int offset_y = 30;         // Position Y de la minimap
    int map_width, map_height; // Dimensions de la minimap
    
    // Calculer la largeur et la hauteur de la minimap
    map_width = game->map.width * size;
    map_height = game->map.height * size;
    
    // Limiter la taille maximale de la minimap
    int max_map_size = 200;
    if (map_width > max_map_size) {
        size = max_map_size / game->map.width;
        map_width = game->map.width * size;
        map_height = game->map.height * size;
    }
    
    // Dessiner un fond pour la minimap
    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (offset_y + y < WIN_HEIGHT && offset_x + x < WIN_WIDTH)
                game->img_data[(offset_y + y) * (game->size_line / 4) + (offset_x + x)] = 0x222222;
        }
    }
    
    // Dessiner les murs et le sol
    for (int map_y = 0; map_y < game->map.height; map_y++) {
        for (int map_x = 0; map_x < (int)ft_strlen(game->map.grid[map_y]); map_x++) {
            int pixel_x = offset_x + map_x * size;
            int pixel_y = offset_y + map_y * size;
            
            // Couleur selon le type de case
            int color;
            if (game->map.grid[map_y][map_x] == '1')
                color = MAP_WALL_COLOR;
            else if (game->map.grid[map_y][map_x] == '0' || ft_strchr("NSEW", game->map.grid[map_y][map_x]))
                color = MAP_FLOOR_COLOR;
            else
                continue; // Ignorer les autres caractères
            
            // Dessiner le carré avec un petit espace entre chaque case
            for (int y = 1; y < size - 1; y++) {
                for (int x = 1; x < size - 1; x++) {
                    if (pixel_y + y < WIN_HEIGHT && pixel_x + x < WIN_WIDTH)
                        game->img_data[(pixel_y + y) * (game->size_line / 4) + (pixel_x + x)] = color;
                }
            }
        }
    }
    
    // Dessiner la position du joueur (cercle)
    int player_pixel_x = offset_x + (int)(game->player.x * size);
    int player_pixel_y = offset_y + (int)(game->player.y * size);
    int player_radius = 3;
    
    for (int y = -player_radius; y <= player_radius; y++) {
        for (int x = -player_radius; x <= player_radius; x++) {
            if (x*x + y*y <= player_radius*player_radius) {
                if (player_pixel_y + y < WIN_HEIGHT && player_pixel_x + x < WIN_WIDTH && 
                    player_pixel_y + y >= 0 && player_pixel_x + x >= 0)
                    game->img_data[(player_pixel_y + y) * (game->size_line / 4) + (player_pixel_x + x)] = MAP_PLAYER_COLOR;
            }
        }
    }
    
    // Dessiner la direction du joueur (ligne)
    int dir_length = size * 2;
    int dir_end_x = player_pixel_x + (int)(game->player.dir_x * dir_length);
    int dir_end_y = player_pixel_y + (int)(game->player.dir_y * dir_length);
    
    draw_line(game, player_pixel_x, player_pixel_y, dir_end_x, dir_end_y, MAP_PLAYER_COLOR);
    
    // Dessiner un cadre autour de la minimap
    draw_minimap_border(game, offset_x, offset_y, map_width, map_height);
}