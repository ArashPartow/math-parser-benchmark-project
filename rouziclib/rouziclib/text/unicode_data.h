enum	// General Category
{
	uccat_Lu,		// Letter, Uppercase
	uccat_Ll,		// Letter, Lowercase
	uccat_Lt,		// Letter, Titlecase
	uccat_Lm,		// Letter, Modifier
	uccat_Lo,		// Letter, Other
	uccat_Mn,		// Mark, Non-Spacing
	uccat_Mc,		// Mark, Spacing Combining
	uccat_Me,		// Mark, Enclosing
	uccat_Nd,		// Number, Decimal Digit
	uccat_Nl,		// Number, Letter
	uccat_No,		// Number, Other
	uccat_Pc,		// Punctuation, Connector
	uccat_Pd,		// Punctuation, Dash
	uccat_Ps,		// Punctuation, Open
	uccat_Pe,		// Punctuation, Close
	uccat_Pi,		// Punctuation, Initial quote (may behave like Ps or Pe depending on usage)
	uccat_Pf,		// Punctuation, Final quote (may behave like Ps or Pe depending on usage)
	uccat_Po,		// Punctuation, Other
	uccat_Sm,		// Symbol, Math
	uccat_Sc,		// Symbol, Currency
	uccat_Sk,		// Symbol, Modifier
	uccat_So,		// Symbol, Other
	uccat_Zs,		// Separator, Space
	uccat_Zl,		// Separator, Line
	uccat_Zp,		// Separator, Paragraph
	uccat_Cc,		// Other, Control
	uccat_Cf,		// Other, Format
	uccat_Cs,		// Other, Surrogate
	uccat_Co,		// Other, Private Use
	uccat_Cn,		// Other, Not Assigned (no characters in the file have this property)
	uccat_count
};


enum	// Bidirectional Category
{
	bidicat_L,		// Left-to-Right
	bidicat_LRE,		// Left-to-Right Embedding
	bidicat_LRO,		// Left-to-Right Override
	bidicat_R,		// Right-to-Left
	bidicat_AL,		// Right-to-Left Arabic
	bidicat_RLE,		// Right-to-Left Embedding
	bidicat_RLO,		// Right-to-Left Override
	bidicat_PDF,		// Pop Directional Format
	bidicat_EN,		// European Number
	bidicat_ES,		// European Number Separator
	bidicat_ET,		// European Number Terminator
	bidicat_AN,		// Arabic Number
	bidicat_CS,		// Common Number Separator
	bidicat_NSM,		// Non-Spacing Mark
	bidicat_BN,		// Boundary Neutral
	bidicat_B,		// Paragraph Separator
	bidicat_S,		// Segment Separator
	bidicat_WS,		// Whitespace
	bidicat_ON,		// Other Neutrals
	bidicat_count
};

enum	// Character Decomposition Mapping
{
	decomp_font,		// A font variant (e.g. a blackletter form).
	decomp_noBreak,		// A no-break version of a space or hyphen.
	decomp_initial,		// An initial presentation form (Arabic).
	decomp_medial,		// A medial presentation form (Arabic).
	decomp_final,		// A final presentation form (Arabic).
	decomp_isolated,	// An isolated presentation form (Arabic).
	decomp_circle,		// An encircled form.
	decomp_super,		// A superscript form.
	decomp_sub,		// A subscript form.
	decomp_vertical,	// A vertical layout presentation form.
	decomp_wide,		// A wide (or zenkaku) compatibility character.
	decomp_narrow,		// A narrow (or hankaku) compatibility character.
	decomp_small,		// A small variant form (CNS compatibility).
	decomp_square,		// A CJK squared font variant.
	decomp_fraction,	// A vulgar fraction form.
	decomp_compat,		// Otherwise unspecified compatibility character.
	decomp_canonical,	// when nothing is specified, it's a canonical mapping
	decomp_count
};

typedef struct
{
	uint32_t codepoint;
	char *name;
	int8_t uccat, bidicat, decomp_type;
	uint32_t combo1, combo2;	// there can more than 2 decomposition components however I don't care
	uint32_t upper_map, lower_map;	// upper and lower case mappings (one or the other)
} unicode_data_t;

extern const char *get_ucd_cat(int cattype, int cat);
extern unicode_data_t *load_unicode_data_from_file(uint8_t *ucd_path, int16_t **codepoint_lut);
extern void init_unicode_data();
extern unicode_data_t get_unicode_data(uint32_t c);
extern void make_unicode_data_table_file();

extern const char *uccat_name[];
extern const char *bidicat_name[];
extern const char *decomp_name[];
extern const char *uccat_desc[];
extern const char *bidicat_desc[];
extern const char *decomp_desc[];
