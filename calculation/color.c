/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:35:30 by jinheo            #+#    #+#             */
/*   Updated: 2023/03/02 19:35:36 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"
#include "macro.h"
#include "struct.h"
#include <math.h>
#include <stdlib.h>

t_color	common_light(t_hittable *world, t_record *hit_record)
{
	t_color	common;
	t_color	glowing;

	common = v_add(world->ambiance, light_from_spot(hit_record, world));
	glowing = v_mul_scalar(hit_record->suface.color,
			hit_record->suface.brightness_rate);
	common = v_add(common, glowing);
	limit_color_brightness(&common);
	return (common);
}

t_color	diffuse_light(t_hittable *world, t_record *hit_record,
	t_color common, int depth)
{
	t_color		diffuse;

	diffuse = ray_color(diffuse_ray(*hit_record), world, depth - 1);
	diffuse = v_add(diffuse, common);
	diffuse = v_mul(diffuse, hit_record->suface.color);
	diffuse = v_mul_scalar(diffuse, 1.0 / 255);
	diffuse = v_mul_scalar(diffuse, hit_record->suface.diffuse_rate);
	limit_color_brightness(&diffuse);
	return (diffuse);
}

t_color	far_dist_fadeness(t_color sum,
	t_color background, double attenuation_rate)
{
	t_color	ret;

	ret = v_init(0, 0, 0);
	ret = v_add(ret, v_mul_scalar(sum, attenuation_rate));
	ret = v_add(ret, v_mul_scalar(background, 1 - attenuation_rate));
	limit_color_brightness(&ret);
	return (ret);
}

int	within_visual_range(t_ray ray, t_record *record)
{
	if (v_length_squared(v_sub(ray.origin, record->origin))
		<= MAX_DIST * MAX_DIST)
		return (1);
	return (0);
}

t_color	ray_color(t_ray ray, t_hittable *world, int depth)
{
	t_record	hit_record;
	t_color		diffuse;
	t_color		specular;
	t_color		common;
	t_color		sum;

	hit_record.origin = v_init(INF, INF, INF);
	if (depth < 0)
		return (v_init(0, 0, 0));
	else if (hit(ray, world, &hit_record)
		&& within_visual_range(ray, &hit_record))
	{
		common = common_light(world, &hit_record);
		diffuse = diffuse_light(world, &hit_record, common, depth - 1);
		specular = ray_color(specular_ray(ray, hit_record), world, depth - 1);
		specular = v_add(specular, common);
		specular = v_mul_scalar(specular, hit_record.suface.specular_rate);
		limit_color_brightness(&specular);
		sum = v_add(diffuse, specular);
		limit_color_brightness(&sum);
		return (far_dist_fadeness(sum, world->background,
				attenuation(ray.origin, hit_record.origin)));
	}
	return (world->background);
}
