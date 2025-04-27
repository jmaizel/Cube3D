/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:10:35 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/27 17:13:47 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define WEAPON_OFFSET_X 100
#define WEAPON_OFFSET_Y 30

/* Dessine l'arme en bas de l'écran */
void draw_weapon(t_game *game)
{
    int x;
    int y;
    int draw_x;
    int draw_y;
    int color;
    int start_x;
    int start_y;
    int current_frame;
    
    // Déterminer quelle frame utiliser
    if (game->weapon_animating)
        current_frame = game->current_weapon_frame;
    else
        current_frame = 0;  // Frame au repos
    
    // Vérifier que nous avons des frames
    if (!game->weapon_frames[current_frame].data)
        return;
    
    start_x = WIN_WIDTH / 2 - game->weapon_frames[current_frame].width / 2 + 30;
    start_y = WIN_HEIGHT - game->weapon_frames[current_frame].height + 10;
    
    y = 0;
    while (y < game->weapon_frames[current_frame].height)
    {
        x = 0;
        while (x < game->weapon_frames[current_frame].width)
        {
            color = game->weapon_frames[current_frame].data[y * game->weapon_frames[current_frame].width + x];
            if ((color & 0x00FFFFFF) != 0x000000) // ignore le noir
            {
                draw_x = start_x + x;
                draw_y = start_y + y;
                if (draw_x >= 0 && draw_x < WIN_WIDTH && draw_y >= 0
                    && draw_y < WIN_HEIGHT)
                    game->img_data[draw_y * (game->size_line / 4)
                        + draw_x] = color;
            }
            x++;
        }
        y++;
    }
}