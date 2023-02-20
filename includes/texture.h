#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef struct s_texture {
  int checkerboard;
  t_vec3 rgb;
  float  diffuse_rate;
  float  specular_rate;
  float  brightness_rate;
} t_texture;

#endif
