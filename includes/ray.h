#ifndef RAY_H
#define RAY_H
#include "color.h"
#include "vec3.h"

typedef t_vec3 t_point3;

typedef struct s_ray {
  t_point3 origin;
  t_vec3 direction;
  t_texture color;
} t_ray;

t_ray ambient_reflection(t_ray *incident, t_ray *normal);
t_ray diffuse_reflection(t_ray *incident, t_ray *normal);
t_ray specular_reflection(t_ray *incident, t_ray *normal);

#endif
