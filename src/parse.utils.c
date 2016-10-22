# include "rt.h"

t_color  read_color(char *data)
{
  t_color new;
  char **vals;

  new = color_new(0, 0, 0);
  if (!ft_strcmp(data, "NULL"))
    return (new);
  vals = ft_strsplit(data, ';');
  if (vals[0] && vals[1] && vals[2])
  {
    new.r = ft_atoi(vals[0]);
    new.g = ft_atoi(vals[1]);
    new.b = ft_atoi(vals[2]);
  }
  ctab_free(vals);
  return (new);
}

t_vect  read_vec(char *data)
{
  t_vect new;
  char **vals;

  new = vec_new(0, 0, 0);
  if (!ft_strcmp(data, "NULL"))
    return (new);
  vals = ft_strsplit(data, ';');
  if (vals[0] && vals[1] && vals[2])
  {
    new.x = ft_atof(vals[0]);
    new.y = ft_atof(vals[1]);
    new.z = ft_atof(vals[2]);
  }
  ctab_free(vals);
  return (new);
}

int     ft_sii(char *s, char *e)
{
  int is;
  int ie;

  is = -1;
  while (s[++is])
  {
    ie = 0;
    while (s[is + ie] && e[ie] &&
    s[is + ie] == e[ie])
      ++ie;
    if (!e[ie])
      return (1);
  }
  return (0);
}

char    *get_after(char *s, char *a)
{
  while (*s == ' ' || *s == '\t')
    s++;
  while (*s == *a && (++s))
    ++a;
  while (*s == ' ' || *s == '\t')
    s++;
  return (s);
}

void ctab_free(char **t)
{
  int i;

  i = -1;
  while (t[++i])
    free(t[i]);
}
