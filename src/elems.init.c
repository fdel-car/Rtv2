# include "rt.h"

t_mater init_mater(void)
{
  t_mater new;

  new.shiny = 0;
  new.int_refl = 0;
  new.int_trans = 0;
  new.color = color_new(0, 0, 0);
  new.text = 0;
  return (new);
}
