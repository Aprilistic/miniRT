#include "ray.h"
#ifndef BRIGHT_SPOT_H
#define BRIGHT_SPOT_H

#include "color.h"
#include "vec3.h"

typedef struct s_bright_spot {
  t_point3 point;
  t_texture color;
} t_bright_spot;

#endif
