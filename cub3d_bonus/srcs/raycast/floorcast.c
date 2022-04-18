/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:29:03 by anremiki          #+#    #+#             */
/*   Updated: 2022/04/18 16:04:41 by anremiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	floorcast(t_cub *cub, t_ray *ray)
{
	//float			distx;
	//float			disty;
	float			fix;
	unsigned int	color;

	ray->j = ray->offset + ray->raycast;
	fix = fix_fisheye(cub->a, ray->ra, 1);
	while (ray->j < VRES)
	{
		//distx = cub->x / 2 + cos(ray->ra) * 200 * 64;
		//disty = cub->y / 2 + sin(ray->ra) * 200 * 64;
		ray->offj = ray->j - (HALFVRES * cub->z);
		ray->curr_px = cub->x / 2 + cos(ray->ra) * 200 * 64 / ray->offj / fix;
		ray->next_px = cub->y / 2 + sin(ray->ra) * 200 * 64 / ray->offj / fix;
		//ray->curr_px = distx / ray->offj / fix;
		//ray->next_px = disty / ray->offj / fix;
		color = pxl_from_img(cub, (int)ray->next_px % 64, (int)ray->curr_px % 64, 6);
		//color = shade(color, ray->shadow);
		pxl_to_ray(cub, ray->nr, ray->j, color);
		ray->j++;
	}
}
