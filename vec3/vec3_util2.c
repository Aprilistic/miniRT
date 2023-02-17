/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:45:10 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/17 21:04:32 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	mul_vector(t_vec3 *left, t_vec3 *right)
{
	t_vec3	result;

	result.e[0] = left->e[0] * right->e[0];
	result.e[1] = left->e[1] * right->e[1];
	result.e[2] = left->e[2] * right->e[2];
	return (result);
}

t_vec3	mul_scalar(t_vec3 *vector, double scalar)
{
	t_vec3	result;

	result.e[0] = vector->e[0] * scalar;
	result.e[1] = vector->e[1] * scalar;
	result.e[2] = vector->e[2] * scalar;
	return (result);
}

t_vec3	unit_vector(t_vec3 *vector)
{
	return (mul_scalar(vector, 1 / length(vector)));
}

double	length_squared(t_vec3 *vector)
{
	return (dot_vector(vector, vector));
}

double	length(t_vec3 *vector)
{
	return (sqrt(length_squared(vector)));
}
