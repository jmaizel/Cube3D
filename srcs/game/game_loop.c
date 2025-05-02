/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:38:45 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/02 19:46:39 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Boucle principale du jeu qui gère les updates et le rendu
 */
int	game_loop(t_game *game)
{
	int	victory_result;

	calculate_delta_time(game);
	update_weapon_timer(game);
	update_monster_hit_effects(game);
	update_monster_animations(game);
	check_monsters_status(game);
	victory_result = check_door_victory(game);
	if (victory_result != 0)
		return (victory_result);
	update_victory_timer(game);
	handle_movement(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_controls_menu(game);
	if (game->victory_displayed || game->all_monsters_killed)
		draw_victory_message(game);
	usleep(16000);
	return (0);
}
