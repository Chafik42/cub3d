/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarouf <cmarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:08:35 by cmarouf           #+#    #+#             */
/*   Updated: 2022/05/23 17:55:28 by cmarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_animation_light_red(t_sp *s)
{
	int	i;

	i = -1;
	s->anim_paths[0] = "./bonus/imgs/blue0.xpm";
	s->anim_paths[1] = "./bonus/imgs/blue1.xpm";
	s->anim_paths[2] = "./bonus/imgs/blue2.xpm";
	s->anim_paths[3] = "./bonus/imgs/blue3.xpm";
	s->anim_paths[4] = "./bonus/imgs/blue4.xpm";
	s->anim_paths[5] = "./bonus/imgs/blue5.xpm";
	s->anim_paths[6] = "./bonus/imgs/blue6.xpm";
	s->anim_paths[7] = "./bonus/imgs/blue7.xpm";
	while (++i < 8)
		if (open(s->anim_paths[i], O_RDONLY) < 1)
			return (0);
	return (1);
}

static int	gather_anim_frames(t_anim *anim, char *anim_path, t_cub *cub)
{
	anim->img = mlx_xpm_file_to_image(cub->mlx, anim_path,
			&anim->a, &anim->b);
	if (!anim->img)
		return (0);
	anim->addr = mlx_get_data_addr(anim->img, &anim->bpp,
			&anim->size, &anim->end);
	return (1);
}

static int	init_animation(t_sp *s, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NB_FRAME)
	{
		s->anim[i].img = NULL;
		s->anim[i].addr = NULL;
		i++;
	}
	i = 0;
	while (i < NB_FRAME)
	{
		if (gather_anim_frames(&s->anim[i], s->anim_paths[i], cub) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	txt_light_red(t_sp *sp, t_cub *cub)
{
	sp->img = NULL;
	if (check_animation_light_red(sp) == 0)
		return (0);
	if (init_animation(sp, cub) == 0)
		return (0);
	sp->img = mlx_xpm_file_to_image(cub->mlx, "./bonus/imgs/blue7.xpm",
			&sp->a, &sp->b);
	if (!sp->img)
		return (0);
	sp->csp.moveable = 1;
	sp->animated = 1;
	sp->hue = RED;
	sp->csp.type = LIGHT;
	return (1);
}