extern uint32_t rand_xsm32_state;

extern uint32_t rand_xsm32(uint32_t x);
extern uint32_t rand32();
extern double randrange(double low, double high);
extern double gaussian_rand();
extern xy_t gaussian_rand_xy();
extern double gaussian_rand_approx();
extern double gaussian_rand_approx_pos(uint32_t pos);
extern xy_t gaussian_rand_approx_xy();

/*extern int pow_mod(int base, uint32_t expon, uint32_t mod);
extern uint32_t rand_minstd(uint32_t pos);
extern uint32_t rand_minstd16(uint32_t pos);
extern uint32_t rand_minstd32(uint32_t pos);
extern double rand_minstd_01(uint32_t pos);
extern double rand_minstd_exc01(uint32_t pos);
extern double gaussian_rand_minstd(uint32_t pos);
extern double gaussian_rand_minstd_approx(uint32_t pos);*/
