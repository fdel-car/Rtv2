void	uctab_free(unsigned char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
}

void free_genv(void)
{
	if (g_env)
	{
		free(g_env.scene.name);
		free_objs(g_env.scene.obj);
		free_lgts(g_env.scene.lgt);
	}
}

void	free_objs(t_obj *o)
{
	while (o)
	{
		free(name);
		free(src);
		if (o->lst)
			free_objs(o->lst);
		free_mater(o->mater);
		o = o->next;
	}
}

void	free_lgts(t_light *l)
{
	while (l)
	{
		free(name);
		free_mater(l->mater);
		l = l->next;
	}
}

void	free_text(t_text *t)
{
	if (!m)
		return ;
	uctab_free(t.text);
	free(t);
}

void	free_mater(t_mater m)
{
	if (m.tex)
		free_text(m.tex.text);
	if (m.ntex)
		free_text(m.ntex.text);
	if (m.ctex)
		free_text(m.ctex.text);
	if (m.ttex)
		free_text(m.ttex.text);
}
