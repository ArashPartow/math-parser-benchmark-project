// in vector_type/vector_type_struct.h:
// letter_t, vector_font_t

#define ALIG_LEFT	0
#define ALIG_CENTRE	1
#define ALIG_RIGHT	2
#define PROPORTIONAL	0
#define MONOSPACE	4
#define MONODIGITS	8
#define ALIG_TOP	16

// TODO put that into font struct
#define LETTERSPACING	1.5	// spacing between each letter
#define LINEVSPACING	10.	// offset for each line
#define LOWERCASESCALE	0.75

extern int get_letter_index(vector_font_t *font, uint32_t c);
extern letter_t *get_letter(vector_font_t *font, uint32_t c);
extern vobj_t *get_letter_obj(vector_font_t *font, uint32_t c);
extern char *get_letter_glyphdata(vector_font_t *font, uint32_t c);
extern letter_t *get_dominant_letter(vector_font_t *font, uint32_t c, int *lowerscale);
extern uint32_t substitute_rtl_punctuation(uint32_t c);

#ifdef RL_INCL_VECTOR_TYPE_FILEBALL
extern void vector_font_load_from_header();
#endif
