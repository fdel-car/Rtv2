#include "rt.h"

t_vect vec_new(float x, float y, float z)
{
  t_vect new;

  new.x = x;
  new.y = y;
  new.z = z;

  return (new);
}

t_color color_new(unsigned char r, unsigned char g, unsigned char b)
{
    t_color new;

    new.r = r;
    new.g = g;
    new.b = b;
    return (new);
}
