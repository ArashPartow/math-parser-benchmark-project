typedef struct
{
	int set_bounds, set_vbounds, pid[400], lineA[400], lineB[400];
	xy_t pv[400];
} glyphdata_t;

extern void font_alloc_one(vector_font_t *font);
extern void font_create_letter(vector_font_t *font, uint32_t cp);
extern void font_remove_letter(vector_font_t *font, uint32_t cp);
extern void add_codepoint_letter_lut_reference(vector_font_t *font);
extern void process_glyphdata(vector_font_t *font, letter_t *l, glyphdata_t *gd);
extern void make_glyph_vobj(letter_t *l, glyphdata_t *gd);
extern void process_one_glyph(vector_font_t *font, int i);
extern vector_font_t *make_font(char *index_path);
extern vector_font_t *make_font_from_fileball(fileball_t *s, const char *index_filename);
extern vector_font_t *make_font_from_zball(uint8_t *data, size_t data_len);
extern void clear_font_vobjs(vector_font_t *font);
extern void free_font(vector_font_t *font);
extern vector_font_t *remake_font(char *index_path, vector_font_t *oldfont);
extern void save_font(vector_font_t *font, char *index_path);

/*
Available commands in range files:

glyph		<codepoint>
subglyph	<ID char>
subend
p<n>		<x>	<y>
lines		<list of points>
copy		<codepoint>  (<ID char of subglyph>)
bounds		<left>	<right>
vbounds		<bottom> <top>
clear_bounds
curveseg	p<n>	<angle>(a)  <length>(x)
rect		p<first_n>  <p0 x y>  <p1 x y>
circle		p<first_n>  p<last_n>  <num seg>  <radius>  <centre x y>  <start angle>
mirror		h/v  <mirror_pos>  p<first_n>  p<last_n>  p<start>

	the following commands can be followed by an optional 'all', 'loc' or 'last'

scale		<scale>
scale		<scale x y>  (<centre x y>)
move		<x>	<y>
rotate		<angle>	 (<centre x y>)
shearX		<angle>	 (<centre x y>)
shearY		<angle>	 (<centre x y>)
*/
