#ifndef FUNCTION_H
# define FUNCTION_H

#include "includes/vec3.h"
#include "struct.h"

/*	t_vec3 */
/* initialize */
t_vec3	v_init(double e0, double e1, double e2);

/* unit vector */
t_vec3	v_unit(t_vec3 *vector);

/* length */
double	v_length(t_vec3 *vector);
double	v_length_squared(t_vec3 *vector);

/* addition, subtraction, dot, cross, mul vector, mul scalar */
t_vec3	v_add(t_vec3 *left, t_vec3 *right);
t_vec3	v_sub(t_vec3 *left, t_vec3 *right);
double	v_dot(t_vec3 *left, t_vec3 *right);
t_vec3	v_cross(t_vec3 *left, t_vec3 *right);
t_vec3	v_mul(t_vec3 *left, t_vec3 *right);
t_vec3	v_mul_scalar(t_vec3 *vector, double scalar);

t_color	init_color(double r, double g, double b);
t_color	ray_color(t_ray ray, t_hittable *world, int depth);
double	random_double(double min, double max);
t_ray	diffuse_ray(t_ray incident, t_record hit_record);
t_ray	specular_ray(t_ray incident, t_record hit_record);

#endif
