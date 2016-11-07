#include "rt.h"

void count_values(char **file, int *v_size, int *vn_size)
{
	int i;

	i = 0;
	while (file[i] && !ft_sii(file[i], "v "))
		++i;
	while (file[i] && ft_sii(file[i], "v "))
	{
		(*v_size)++;
		++i;
	}
	while (file[i] && !ft_sii(file[i], "vn "))
		++i;
	while (file[i] && ft_sii(file[i++], "vn "))
		(*vn_size)++;
}

int get_val(char *s, int r)
{
	int i;
	int c;

	i = -1;
	c = 1;
	while (s[++i] && c < r)
		s[i] == '/' || s[i] == ' ' ? ++c : 0;
	return (ft_atoi(&(s[i])));
}

void read_triangle(t_obj *o, char *line, t_vect **v, t_mater mat)
{
	char **t;

	t = ft_strsplit(line, ' ');
	if (t[0] && t[1] && t[2] && t[3])
	{
			o->name = ft_strdup("mesh_triangle");
			o->type = TRIANGLE;
			o->norm = v[1][get_val(t[1], 3) - 1];
			o->v0 = v[0][get_val(t[1], 1) - 1];
			o->v1 = v[0][get_val(t[2], 1) - 1];
			o->v2 = v[0][get_val(t[3], 1) - 1];
			o->mater = mat;
			o->next = 0;
	}
	ctab_free(t);
}

void load_obj(char **file, t_vect **v, int i, t_mater mat)
{
	t_obj *new;

	while (file[i] && !ft_sii(file[i], "f "))
		++i;
	while (file[i])
	{
		new = malloc(sizeof(t_obj));
		read_triangle(new, file[i], v, mat);
		set_func(new);
		push_obj(new);
		++i;
	}
}

void fill_values(char **file, int v_s, int vn_s, t_mater mat)
{
	t_vect *v[2];
	int i;
	int in;

	i = 0;
	v[0] = malloc(sizeof(t_vect) * (v_s + 1));
	v[1] = malloc(sizeof(t_vect) * (vn_s + 1));
	while (file[i] && !ft_sii(file[i], "v "))
		++i;
	in = 0;
	while (file[i] && ft_sii(file[i], "v "))
			v[0][in++] = read_vec(get_after(file[i++], "v "), ' ');
	while (file[i] && !ft_sii(file[i], "vn "))
		++i;
	in = 0;
	while (file[i] && ft_sii(file[i], "vn "))
			v[1][in++] = read_vec(get_after(file[i++], "vn "), ' ');
	load_obj(file, v, i, mat);
}

void parse_obj(char *file_name, t_mater mat)
{
	int		fd;
	char	*line;
	char	*file[9999];
	int		n;
	int 	size[2];//v / vn

	n = -1;
	size[0] = 0;
	size[1] = 0;
	if ((fd = open(file_name, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) && (++n) > -42)
			file[n] = line;
		file[n + 1] = 0;
		count_values(file, &size[0], &size[1]);
		fill_values(file, size[0], size[1], mat);
		ctab_free(file);
	}
}
