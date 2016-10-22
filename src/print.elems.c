#include "rt.h"

void print_obj()
{
  t_obj *c;

  printf("objs\n");
  c = g_env.scene.obj;
  while (c)
  {
    printf("name: %s\n", c->name);
    printf("pos: %f %f %f\n", c->pos.x, c->pos.y, c->pos.z);
    printf("----\n");

    c = c->next;
  }
  printf("---------\n");
}

void print_lgt()
{
  t_light *c;

  c = g_env.scene.lgt;
  while (c)
  {
    printf("name: %s\n", c->name);
    printf("pos: %f %f %f\n", c->pos.x, c->pos.y, c->pos.z);
    printf("----\n");

    c = c->next;
  }
  printf("---------\n");

}
