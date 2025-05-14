/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:38:21 by cdedessu          #+#    #+#             */
/*   Updated: 2025/05/14 10:42:24 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	prepare_texture_params(t_ray *ray, t_texture *tex, t_tex_params *params)
{
	double	wall_x;
	int		tex_x;

	calculate_texture_x(ray, &wall_x, &tex_x, tex);
	params->step = 1.0 * tex->height / ray->line_height;
	params->tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * params->step;
	params->tex_x = tex_x;
}
