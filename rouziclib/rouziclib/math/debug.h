typedef struct
{
	char *name;
	int p_count;
	xy_t *p;
} math_graph_t;

typedef struct
{
	volatile int init;
	rl_mutex_t mutex;
	volatile size_t count, as;
	math_graph_t *graph;
} math_graph_array_t;

extern math_graph_array_t graph_array;

extern void math_graph_add(double *x, double *y, int p_count, char *name);
extern void math_graph_add_y(double *y, int p_count, char *name);
extern void math_graph_add_xy(xy_t *p, int p_count, char *name);
extern void free_math_graph(math_graph_t *mg);
extern void free_math_graph_array();
extern void lock_math_graph();
extern void unlock_math_graph();
extern double math_graph_get_interpolated_value(int index, double x);
