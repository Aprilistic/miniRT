/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:37:23 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/17 20:50:06 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	init_vector(t_vec3 *vec, double e0, double e1, double e2)
{
	vec->e[0] = e0;
	vec->e[1] = e1;
	vec->e[2] = e2;
}

t_vec3	add_vector(t_vec3 *left, t_vec3 *right)
{
	t_vec3	result;

	result.e[0] = left->e[0] + right->e[0];
	result.e[1] = left->e[1] + right->e[1];
	result.e[2] = left->e[2] + right->e[2];
	return (result);
}

t_vec3	sub_vector(t_vec3 *left, t_vec3 *right)
{
	t_vec3	result;

	result.e[0] = left->e[0] - right->e[0];
	result.e[1] = left->e[1] - right->e[1];
	result.e[2] = left->e[2] - right->e[2];
	return (result);
}

double	dot_vector(t_vec3 *left, t_vec3 *right)
{
	return (left->e[0] * right->e[0]
		+ left->e[1] * right->e[1]
		+ left->e[2] * right->e[2]);
}

t_vec3	cross_vector(t_vec3 *left, t_vec3 *right)
{
	t_vec3	result;

	result.e[0] = left->e[1] * right->e[2] - left->e[2] * right->e[1];
	result.e[1] = left->e[2] * right->e[0] - left->e[0] * right->e[2];
	result.e[2] = left->e[0] * right->e[1] - left->e[1] * right->e[0];
	return (result);
}
