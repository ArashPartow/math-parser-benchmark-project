#ifndef RL_EXCL_APPROX

extern float fastcosf_tr_d2(float x);
extern double fastcos_tr_d2(double x);
extern double fastcos_tr_d3(double x);
extern double fastcos_tr_d4(double x);
extern double fastcos_tr_d5(double x);
extern xy_t fastcos_tr_d3_xy(xy_t v);

#define fastcosf_d2(x)	fastcosf_tr_d2((x)*0.159154943f)
#define fastcos_d2(x)	fastcos_tr_d2((x)*0.15915494309189535)
#define fastcos_d3(x)	fastcos_tr_d3((x)*0.15915494309189535)
#define fastcos_d4(x)	fastcos_tr_d4((x)*0.15915494309189535)
#define fastcos_d5(x)	fastcos_tr_d5((x)*0.15915494309189535)

#define fastsinf_d2(x) fastcosf_d2((x)-0.5*pi)
#define fastsin_d2(x) fastcos_d2((x)-0.5*pi)
#define fastsin_d3(x) fastcos_d3((x)-0.5*pi)
#define fastsin_d4(x) fastcos_d4((x)-0.5*pi)
#define fastsin_d5(x) fastcos_d5((x)-0.5*pi)

#define fastsinf_tr_d2(x) fastcosf_tr_d2((x)-0.25f)
#define fastsin_tr_d2(x) fastcos_tr_d2((x)-0.25)
#define fastsin_tr_d3(x) fastcos_tr_d3((x)-0.25)
#define fastsin_tr_d4(x) fastcos_tr_d4((x)-0.25)
#define fastsin_tr_d5(x) fastcos_tr_d5((x)-0.25)

#else

#define fastcos_d2	cos
#define fastcos_d3	cos
#define fastcos_d4	cos
#define fastcos_d5	cos
#define fastsin_d2	sin
#define fastsin_d3	sin
#define fastsin_d4	sin
#define fastsin_d5	sin
#define fastcos_tr_d2	cos_tr
#define fastcos_tr_d3	cos_tr
#define fastcos_tr_d4	cos_tr
#define fastcos_tr_d5	cos_tr
#define fastsin_tr_d2	sin_tr
#define fastsin_tr_d3	sin_tr
#define fastsin_tr_d4	sin_tr
#define fastsin_tr_d5	sin_tr
#define fastcosf_d2	cosf
#define fastsinf_d2	sinf

#endif
