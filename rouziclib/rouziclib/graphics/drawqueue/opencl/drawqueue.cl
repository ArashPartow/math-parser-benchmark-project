// cd ~/../rouziclib/graphics/drawqueue/opencl/ && cp drawqueue.cl drawqueue.cl.c && gcc -E -P drawqueue.cl.c | dos2unix > dq.cl && bin_to_c dq.cl && mv dq.cl.h drawqueue.cl.h && rm drawqueue.cl.c dq.cl

#include "../drawqueue_enums.h"
#include "gaussian.cl"
#include "trig.cl"
#include "blending.cl"
#include "drawline.cl"
#include "drawrect.cl"
#include "drawcircle.cl"
#include "drawtriangle.cl"
#include "srgb.cl"
#include "colour.cl"
#include "bits.cl"
#include "blit.cl"

float4 drawgradienttest(float4 pv)
{
	const float2 pf = (float2) (get_global_id(0), get_global_id(1));
	const float2 ss = (float2) (get_global_size(0), get_global_size(1));
	const float2 c = ss * 0.5f;

	pv = -(pf.x - c.x) / (ss.x * 0.1f);

	return pv;
}

float4 draw_queue(global float *df, global int *poslist, global int *entrylist, global uchar *data_cl, const int sector_w, const int sector_size)
{
	const int2 p = (int2) (get_global_id(0), get_global_id(1));
	const float2 pf = convert_float2(p);
	const int sec = (p.y >> sector_size) * sector_w + (p.x >> sector_size);	// sector index
	global int *di = (global int *) df;	// main queue pointer
	int i, eli, entry_count, qi;
	float4 pv = 0.f;		// pixel value (linear)
	int brlvl = 0;			// bracket level
	float4 br[4];			// bracket pixels

	eli = poslist[sec];		// entry list index

	if (eli < 0)			// if the index is -1
		return pv; 		// that means there's nothing to do

	entry_count = entrylist[eli];

	for (i=0; i < entry_count; i++)
	{
		qi = entrylist[eli + i + 1];	// queue index

		switch (di[qi])			// type of the entry
		{
			case DQT_BRACKET_OPEN:
				br[brlvl] = pv;
				pv = 0.f;
				brlvl++;
				break;

			case DQT_BRACKET_CLOSE:
				brlvl--;
				pv = blend_pixel(br[brlvl], pv, di[qi+1]);
				break;

				case DQT_LINE_THIN_ADD:		pv = draw_line_thin_add(&df[qi+1], pv, pf);
			break;	case DQT_POINT_ADD:		pv = draw_point_add(&df[qi+1], pv, pf);
			break;	case DQT_RECT_FULL:		pv = draw_rect_full_add(&df[qi+1], pv, pf);
			break;	case DQT_RECT_BLACK:		pv = draw_black_rect(&df[qi+1], pv, pf);
			break;	case DQT_RECT_BLACK_INV:	pv = draw_black_rect_inv(&df[qi+1], pv, pf);
			break;	case DQT_PLAIN_FILL:		pv = draw_plain_fill_add(&df[qi+1], pv);
			break;	case DQT_TRIANGLE:		pv = draw_triangle(&df[qi+1], pv, pf);
			break;	case DQT_TETRAGON:		pv = draw_tetragon(&df[qi+1], pv, pf);
			break;	case DQT_GAIN:			pv = pv * df[qi+1];
			break;	case DQT_GAIN_PARAB:		pv = gain_parabolic(pv, df[qi+1]);
			break;	case DQT_LUMA_COMPRESS:		pv = luma_compression(pv, df[qi+1]);
			break;	case DQT_COL_MATRIX:		pv = colour_matrix(&df[qi+1], pv);
			break;	case DQT_CLIP:			pv = min(pv, df[qi+1]);
			break;	case DQT_CLAMP:			pv = clamp(pv, 0.f, 1.f);
			break;	case DQT_CIRCLE_FULL:		pv = draw_circle_full_add(&df[qi+1], pv, pf);
			break;	case DQT_CIRCLE_HOLLOW:		pv = draw_circle_hollow_add(&df[qi+1], pv, pf);
			//break;	case DQT_BLIT_BILINEAR:	pv = blit_sprite_bilinear(&df[qi+1], data_cl, pv);
			break;	case DQT_BLIT_FLATTOP:		pv = blit_sprite_flattop((global uint *) &di[qi+1], data_cl, pv, pf);
			break;	case DQT_BLIT_FLATTOP_ROT:	pv = blit_sprite_flattop_rot((global uint *) &di[qi+1], data_cl, pv, pf);
			break;	case DQT_BLIT_AANEAREST:	pv = blit_sprite_aa_nearest((global uint *) &di[qi+1], data_cl, pv, pf);
			break;	case DQT_BLIT_AANEAREST_ROT:	pv = blit_sprite_aa_nearest_rot((global uint *) &di[qi+1], data_cl, pv, pf);
			//break;	case DQT_BLIT_PHOTO:		pv = blit_photo(&df[qi+1], data_cl, pv);
			break;	case DQT_TEST1:			pv = drawgradienttest(pv);

			default:
				break;
		}
	}

	return pv;
}

kernel /*__attribute__((reqd_work_group_size(16,16,1)))*/ void draw_queue_srgb_kernel(const ulong df_index, const ulong poslist_index, const ulong entrylist_index, global uchar *data_cl, write_only image2d_t srgb, const int sector_w, const int sector_size, const int randseed)
{
	const int2 p = (int2) (get_global_id(0), get_global_id(1));
	const int fbi = p.y * get_global_size(0) + p.x;
	float4 pv;		// pixel value (linear)
	global float *df = (global float *) &data_cl[df_index];
	global int *poslist = (global int *) &data_cl[poslist_index];
	global int *entrylist = (global int *) &data_cl[entrylist_index];

	pv = draw_queue(df, poslist, entrylist, data_cl, sector_w, sector_size);

	if (pv.s0==0.f)
	if (pv.s1==0.f)
	if (pv.s2==0.f)
	{
		write_imageui(srgb, p, 0);
		return ;
	}

	write_imagef(srgb, p, linear_to_srgb(pv, randseed+fbi));
}

kernel void draw_queue_srgb_buf_kernel(const ulong df_index, const ulong poslist_index, const ulong entrylist_index, global uchar *data_cl, global uchar4 *srgb, const int sector_w, const int sector_size, const int randseed)
{
	const int2 p = (int2) (get_global_id(0), get_global_id(1));
	const int fbi = p.y * get_global_size(0) + p.x;
	float4 pv;		// pixel value (linear)
	uchar4 ps;
	global float *df = (global float *) &data_cl[df_index];
	global int *poslist = (global int *) &data_cl[poslist_index];
	global int *entrylist = (global int *) &data_cl[entrylist_index];

	pv = draw_queue(df, poslist, entrylist, data_cl, sector_w, sector_size);

	if (pv.s0==0.f)
	if (pv.s1==0.f)
	if (pv.s2==0.f)
	{
		srgb[fbi] = 0;
		return ;
	}

	ps = convert_uchar4(linear_to_srgb(pv, randseed+fbi) * 255.f);
	srgb[fbi].x = ps.z;
	srgb[fbi].y = ps.y;
	srgb[fbi].z = ps.x;
}
