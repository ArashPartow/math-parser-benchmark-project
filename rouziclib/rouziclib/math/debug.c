math_graph_array_t graph_array={0};

math_graph_t *math_graph_alloc_one()
{
	if (graph_array.init==0)
	{
		graph_array.init = 1;
		rl_mutex_init(&graph_array.mutex);
	}

	alloc_enough_mutex(&graph_array.graph, graph_array.count+=1, &graph_array.as, sizeof(math_graph_t), 1.5, &graph_array.mutex);

	return &graph_array.graph[graph_array.count-1];
}

void math_graph_sort(math_graph_t *mg)
{
	qsort(mg->p, mg->p_count, sizeof(xy_t), cmp_xy_by_x);
}

void math_graph_add(double *x, double *y, int p_count, char *name)
{
	int i;
	math_graph_t *mg = math_graph_alloc_one();

	mg->p_count = p_count;
	mg->p = calloc(p_count, sizeof(xy_t));
	mg->name = make_string_copy(name);

	for (i=0; i < p_count; i++)
		mg->p[i] = xy(x[i], y[i]);

	math_graph_sort(mg);
}

void math_graph_add_y(double *y, int p_count, char *name)
{
	int i;
	math_graph_t *mg = math_graph_alloc_one();

	mg->p_count = p_count;
	mg->p = calloc(p_count, sizeof(xy_t));
	mg->name = make_string_copy(name);

	for (i=0; i < p_count; i++)
		mg->p[i] = xy(i, y[i]);

	math_graph_sort(mg);
}

void math_graph_add_xy(xy_t *p, int p_count, char *name)
{
	int i;
	math_graph_t *mg = math_graph_alloc_one();

	mg->p_count = p_count;
	mg->p = calloc(p_count, sizeof(xy_t));
	mg->name = make_string_copy(name);

	for (i=0; i < p_count; i++)
		mg->p[i] = p[i];

	math_graph_sort(mg);
}

void free_math_graph(math_graph_t *mg)
{
	free_null(&mg->name);
	free_null(&mg->p);
	mg->p_count = 0;
}

void free_math_graph_array()
{
	int i;

	for (i=0; i < graph_array.count; i++)
		free_math_graph(&graph_array.graph[i]);

	free_null(&graph_array.graph);
	graph_array.count = 0;
	graph_array.as = 0;
}

void lock_math_graph()
{
	if (graph_array.init==0)
		return;

	rl_mutex_lock(&graph_array.mutex);
}

void unlock_math_graph()
{
	if (graph_array.init==0)
		return;

	rl_mutex_unlock(&graph_array.mutex);
}

double math_graph_get_interpolated_value_core(int index, double x)
{
	int i;
	math_graph_t *mg;
	xy_t p0, p1;
	double t;

	if (index < 0 || index >= graph_array.count)
		return NAN;

	mg = &graph_array.graph[index];
	if (mg==NULL)
		return NAN;

	if (x < mg->p[0].x || x > mg->p[mg->p_count-1].x)
		return NAN;

	return get_interpolated_xy_array_value(x, mg->p, mg->p_count);
}

double math_graph_get_interpolated_value(int index, double x)
{
	double y;

	if (graph_array.init==0)
		return NAN;

	lock_math_graph();
	y = math_graph_get_interpolated_value_core(index, x);
	unlock_math_graph();

	return y;
}
