typedef struct
{
	xyz_t p1, p2, r1, r2;
	double m;
} seg_t;

typedef struct
{
	int32_t count;	// number of segments
	double scale;	// on screen scale
	xy_t c;		// centre of rotation/gravity
	seg_t *seg;	// segments
} vobj_t;
