/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:45:10 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/21 20:31:27 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct.h"
#include "../function.h"
#include "../macro.h"

t_vec3	v_mul(t_vec3 *left, t_vec3 *right)
{
	t_vec3	result;

	result.e[0] = left->e[0] * right->e[0];
	result.e[1] = left->e[1] * right->e[1];
	result.e[2] = left->e[2] * right->e[2];
	return (result);
}

t_vec3	v_mul_scalar(t_vec3 *vector, double scalar)
{
	t_vec3	result;

	result.e[0] = vector->e[0] * scalar;
	result.e[1] = vector->e[1] * scalar;
	result.e[2] = vector->e[2] * scalar;
	return (result);
}

t_vec3	v_unit(t_vec3 *vector)
{
	return (v_mul_scalar(vector, 1 / v_length(vector)));
}

double	v_length_squared(t_vec3 *vector)
{
	return (v_dot(vector, vector));
}

double	v_length(t_vec3 *vector)
{
	return (sqrt(v_length_squared(vector)));
}
