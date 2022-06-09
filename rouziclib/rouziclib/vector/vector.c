vobj_t *alloc_vobj(int32_t count)
{
	vobj_t *o;

	o = calloc (1, sizeof(vobj_t));
	o->count = count;
	o->scale = 1.;
	o->c = XY0;

	o->seg = calloc (o->count, sizeof(seg_t));

	return o;
}

void free_vobj(vobj_t *o)
{
	if (o==NULL)
		return ;

	free(o->seg);
	free(o);
}

void join_vobj(vobj_t *o)
{
	int32_t i;

	// join segments together
	for (i=0; i<o->count; i++)
	{
		if (o->seg[i].p1.x==NOC && i>0)
			o->seg[i].p1.x = o->seg[i-1].p2.x;
		if (o->seg[i].p1.y==NOC && i>0)
			o->seg[i].p1.y = o->seg[i-1].p2.y;
		if (o->seg[i].p1.z==NOC && i>0)
			o->seg[i].p1.z = o->seg[i-1].p2.z;

		if (o->seg[i].p2.x==NOC && i!=o->count-1)
			o->seg[i].p2.x = o->seg[i+1].p1.x;
		if (o->seg[i].p2.y==NOC && i!=o->count-1)
			o->seg[i].p2.y = o->seg[i+1].p1.y;
		if (o->seg[i].p2.z==NOC && i!=o->count-1)
			o->seg[i].p2.z = o->seg[i+1].p1.z;
	}

	// join last segment to first point
	i = o->count-1;
	if (o->seg[i].p2.x==NOC)
		o->seg[i].p2.x = o->seg[0].p1.x;
	if (o->seg[i].p2.y==NOC)
		o->seg[i].p2.y = o->seg[0].p1.y;
	if (o->seg[i].p2.z==NOC)
		o->seg[i].p2.z = o->seg[0].p1.z;

	// rescale all
	for (i=0; i<o->count; i++)
	{
		o->seg[i].p1 = mul_xyz(sub_xyz(o->seg[i].p1, xy_to_xyz(o->c)), set_xyz(o->scale));
		o->seg[i].p2 = mul_xyz(sub_xyz(o->seg[i].p2, xy_to_xyz(o->c)), set_xyz(o->scale));
	}
}

vobj_t *make_vobj(int32_t count, double scale, xy_t c)
{
	vobj_t *o;

	o = calloc (1, sizeof(vobj_t));
	o->count = count;
	o->scale = scale;
	o->c = c;

	o->seg = calloc (o->count, sizeof(seg_t));

	return o;
}

vobj_t *duplicate_vobj(vobj_t *o1)
{
	vobj_t *o2;

	if (o1==NULL)
		return NULL;

	o2 = calloc (1, sizeof(vobj_t));
	*o2 = *o1;

	o2->seg = calloc (o2->count, sizeof(seg_t));
	memcpy(o2->seg, o1->seg, o2->count * sizeof(seg_t));

	return o2;
}

vobj_t *cat_vobj(vobj_t *o1, vobj_t *o2, int32_t dofree)
{
	int i;
	vobj_t *o;

	if (o1==NULL || o2==NULL)
		return NULL;

	o = calloc (1, sizeof(vobj_t));
	o->count = o1->count + o2->count;
	o->scale = 1.;
	o->c = XY0;

	o->seg = calloc (o->count, sizeof(seg_t));

	for (i=0; i<o1->count; i++)
		o->seg[i] = o1->seg[i];

	for (i=0; i<o2->count; i++)
		o->seg[i+o1->count] = o2->seg[i];

	if (dofree)
	{
		free_vobj(o1);
		free_vobj(o2);
	}

	return o;
}

vobj_t *scale_vobj(vobj_t *o, xyz_t scale)
{
	int i;

	if (o==NULL)
		return NULL;

	for (i=0; i<o->count; i++)
	{
		o->seg[i].p1 = mul_xyz(o->seg[i].p1, scale);
		o->seg[i].p2 = mul_xyz(o->seg[i].p2, scale);
	}

	return o;
}

seg_t seg_make_xy(xy_t p1, xy_t p2, double m)
{
	seg_t s;

	s.p1 = xy_to_xyz(p1);
	s.p2 = xy_to_xyz(p2);
	s.m = m;

	return s;
}

seg_t seg_make_xyz(xyz_t p1, xyz_t p2, double m)
{
	seg_t s;

	s.p1 = p1;
	s.p2 = p2;
	s.m = m;

	return s;
}

seg_t rot_seg(seg_t seg, double scale, double th)
{
	seg_t rs;
	double z;

	if (th==0. && scale==1.)
		return seg;

	rs.p1 = mul_xyz(seg.p1, set_xyz(scale));
	rs.p2 = mul_xyz(seg.p2, set_xyz(scale));

	if (th==0.)
		return rs;

	z = rs.p1.z;
	rs.p1 = rotate_xy(rs.p1, th);
	rs.p1.z = z;
	z = rs.p2.z;
	rs.p2 = rotate_xy(rs.p2, th);
	rs.p2.z = z;

	return rs;
}

void rot_vobj(vobj_t *o, double x, double y, double scale, double angle)
{
	int32_t i;
	seg_t rs;

	for (i=0; i<o->count; i++)
	{
		rs = rot_seg(o->seg[i], scale, angle);
		o->seg[i].r1.x = rs.p1.x+x;
		o->seg[i].r1.y = rs.p1.y+y;
		o->seg[i].r2.x = rs.p2.x+x;
		o->seg[i].r2.y = rs.p2.y+y;
	}
}

rect_t vobj_bounding_rect(vobj_t *o)
{
	int i;
	rect_t r = rect( xy(FLT_MAX, FLT_MAX), xy(-FLT_MAX, -FLT_MAX) );

	for (i=0; i<o->count; i++)
	{
		r.p0 = min_xy(r.p0, xyz_to_xy(min_xyz(o->seg[i].p1, o->seg[i].p2)));
		r.p1 = max_xy(r.p1, xyz_to_xy(max_xyz(o->seg[i].p1, o->seg[i].p2)));
	}

	return r;
}

void draw_vobj_fullarg(vobj_t *o, xy_t p, xy_t scale, double angle, double line_thick, col_t colour)
{
	int32_t i;
	seg_t rs;

	if (o==NULL)
		return;

	for (i=0; i<o->count; i++)
	{
		rs = rot_seg(o->seg[i], scale.x, angle);

		if (rs.p1.x==rs.p2.x && rs.p1.y==rs.p2.y)	// gaussian dot
			draw_point(xy(rs.p1.x+p.x, -rs.p1.y+p.y), line_thick, colour, cur_blend, o->seg[i].m);
		else
			draw_line_thin(xy(rs.p1.x+p.x, -rs.p1.y+p.y), xy(rs.p2.x+p.x, -rs.p2.y+p.y), line_thick, colour, cur_blend, o->seg[i].m);
	}
}

xy_t *vobj_to_map(vobj_t *o, int32_t dofree)	// naively assumes the vobj is a sequential curve
{
	xy_t *map;
	int32_t i;

	map = calloc (o->count, sizeof(xy_t));

	for (i=0; i<o->count-1; i+=2)
	{
		map[i] = xyz_to_xy(o->seg[i].p1);
		map[i+1] = xyz_to_xy(o->seg[i].p2);
	}
	map[i] = xyz_to_xy(o->seg[i].p1);

	if (dofree)
		free_vobj (o);

	return map;
}

vobj_t *map_to_vobj(xy_t *map, int32_t mapsize, int32_t dofree)
{
	vobj_t *o;
	int32_t i;

	o = make_vobj(mapsize-1, 1., XY0);

	for (i=0; i<mapsize-1; i++)
	{
		o->seg[i].p1 = xy_to_xyz(map[i]);
		o->seg[i].p2 = xy_to_xyz(map[i+1]);
		o->seg[i].m = 1.;
	}
	/*o->seg[i].p1 = xy_to_xyz(map[i]);
	o->seg[i].p2 = xy_to_xyz(map[0]);
	o->seg[i].m = 1.;*/

	if (dofree)
		free (map);

	return o;
}
