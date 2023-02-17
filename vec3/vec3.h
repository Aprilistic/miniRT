/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:35:52 by taeypark          #+#    #+#             */
/*   Updated: 2023/02/17 21:04:51 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>

typedef struct s_vec3
{
	double	e[3];
}	t_vec3;

/* initialize */
void	init_vector(t_vec3 *vec, double e0, double e1, double e2);

/* unit vector */
t_vec3	unit_vector(t_vec3 *vector);

/* length */
double	length(t_vec3 *vector);
double	length_squared(t_vec3 *vector);

/* addition, subtraction, dot, cross, mul vector, mul scalar */
t_vec3	add_vector(t_vec3 *left, t_vec3 *right);
t_vec3	sub_vector(t_vec3 *left, t_vec3 *right);
double	dot_vector(t_vec3 *left, t_vec3 *right);
t_vec3	cross_vector(t_vec3 *left, t_vec3 *right);
t_vec3	mul_vector(t_vec3 *left, t_vec3 *right);
t_vec3	mul_scalar(t_vec3 *vector, double scalar);

#endif
