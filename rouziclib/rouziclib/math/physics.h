extern void add_body_force_xy(xy_t p0, xy_t p1, double mass, xy_t *acc);
extern void add_body_force_xyz(xyz_t p0, xyz_t p1, double mass, xyz_t *acc);
extern void physical_integration_xy(xy_t *pos, xy_t *vel, xy_t acc, double dt);
extern void physical_integration_xyz(xyz_t *pos, xyz_t *vel, xyz_t acc, double dt);
