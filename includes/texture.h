#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef struct s_texture {
  int checkerboard;
  t_vec3 rgb;
  double reflectivity;
  double brightness;
} t_texture;

#endif
