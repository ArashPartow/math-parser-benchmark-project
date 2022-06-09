#include "unicode_data_table.h"
int16_t *codepoint_lut=NULL;

#ifdef RL_INCL_UNICODE_DATA
const char *uccat_name[] = {"Lu", "Ll", "Lt", "Lm", "Lo", "Mn", "Mc", "Me", "Nd", "Nl", "No", "Pc", "Pd", "Ps", "Pe", "Pi", "Pf", "Po", "Sm", "Sc", "Sk", "So", "Zs", "Zl", "Zp", "Cc", "Cf", "Cs", "Co", "Cn"};
const char *bidicat_name[] = {"L", "LRE", "LRO", "R", "AL", "RLE", "RLO", "PDF", "EN", "ES", "ET", "AN", "CS", "NSM", "BN", "B", "S", "WS", "ON"};
const char *decomp_name[] = {"<font>", "<noBreak>", "<initial>", "<medial>", "<final>", "<isolated>", "<circle>", "<super>", "<sub>", "<vertical>", "<wide>", "<narrow>", "<small>", "<square>", "<fraction>", "<compat>"};

const char *uccat_desc[] = {"Lu (Letter, Uppercase)", "Ll (Letter, Lowercase)", "Lt (Letter, Titlecase)", "Lm (Letter, Modifier)", "Lo (Letter, Other)", "Mn (Mark, Non-Spacing)", "Mc (Mark, Spacing Combining)", "Me (Mark, Enclosing)", "Nd (Number, Decimal Digit)", "Nl (Number, Letter)", "No (Number, Other)", "Pc (Punctuation, Connector)", "Pd (Punctuation, Dash)", "Ps (Punctuation, Open)", "Pe (Punctuation, Close)", "Pi (Punctuation, Initial quote)", "Pf (Punctuation, Final quote)", "Po (Punctuation, Other)", "Sm (Symbol, Math)", "Sc (Symbol, Currency)", "Sk (Symbol, Modifier)", "So (Symbol, Other)", "Zs (Separator, Space)", "Zl (Separator, Line)", "Zp (Separator, Paragraph)", "Cc (Other, Control)", "Cf (Other, Format)", "Cs (Other, Surrogate)", "Co (Other, Private Use)", "Cn (Other, Not Assigned)"};
const char *bidicat_desc[] = {"L (Left-to-Right)", "LRE (Left-to-Right Embedding)", "LRO (Left-to-Right Override)", "R (Right-to-Left)", "AL (Right-to-Left Arabic)", "RLE (Right-to-Left Embedding)", "RLO (Right-to-Left Override)", "PDF (Pop Directional Format)", "EN (European Number)", "ES (European Number Separator)", "ET (European Number Terminator)", "AN (Arabic Number)", "CS (Common Number Separator)", "NSM (Non-Spacing Mark)", "BN (Boundary Neutral)", "B (Paragraph Separator)", "S (Segment Separator)", "WS (Whitespace)", "ON (Other Neutrals)"};
const char *decomp_desc[] = {"font (A font variant (e.g. a blackletter form))", "noBreak (A no-break version of a space or hyphen)", "initial (An initial presentation form (Arabic))", "medial (A medial presentation form (Arabic))", "final (A final presentation form (Arabic))", "isolated (An isolated presentation form (Arabic))", "circle (An encircled form)", "super (A superscript form)", "sub (A subscript form)", "vertical (A vertical layout presentation form)", "wide (A wide (or zenkaku) compatibility character)", "narrow (A narrow (or hankaku) compatibility character)", "small (A small variant form (CNS compatibility))", "square (A CJK squared font variant)", "fraction (A vulgar fraction form)", "compat (Otherwise unspecified compatibility character)", "Canonical mapping"};

#else

const char *uccat_name[] = {""};
const char *bidicat_name[] = {""};
const char *decomp_name[] = {""};

const char *uccat_desc[] = {""};
const char *bidicat_desc[] = {""};
const char *decomp_desc[] = {""};

#endif

const char *get_ucd_cat(int cattype, int cat)
{
	char *desc;

	if (cat < 0)
		return "-";

	switch (cattype)
	{
		case 1:
			return uccat_desc[cat];

		case 2:
			return bidicat_desc[cat];

		case 3:
			return decomp_desc[cat];

		default:
			return "?";
	}
}

unicode_data_t *load_unicode_data_from_file(uint8_t *ucd_path, int16_t **codepoint_lut)
{
	FILE *udf;
	int32_t i, ic, linecount=0;
	unicode_data_t *ucd;
	char line[256], a[256], b[256], *p;

	udf = fopen_utf8(ucd_path, "rb");
	if (udf==NULL)
	{
		fprintf_rl(stderr, "UnicodeData.txt file not found.\n");
		return NULL;
	}

	linecount = count_linebreaks(udf) + 1;
	ucd = calloc(linecount, sizeof(unicode_data_t));
	(*codepoint_lut) = calloc (0x110000, sizeof(int16_t));

	ic = 0;
	while (fgets(line, sizeof(line), udf))
	{
		// Field 0: Code point
		if (string_get_field(line, ";", 0, a))
		if (strlen(a) > 0)	// if the field is non-empty
		{
			sscanf(a, "%x", &ucd[ic].codepoint);
			(*codepoint_lut)[ucd[ic].codepoint] = ic;	// put the table ID into the LUT taking codepoints as index
		}

		// Field 1: Character name
		if (string_get_field(line, ";", 1, a))
		if (strlen(a) > 0)
		{
			ucd[ic].name = calloc (strlen(a)+1, sizeof(char));
			strcpy(ucd[ic].name, a);
		}

		// Field 2: General Category
		ucd[ic].uccat = -1;
		if (string_get_field(line, ";", 2, a))
		if (strlen(a) > 0)
		{
			for (i=0; i < sizeof(uccat_name)/sizeof(*uccat_name); i++)
				if (strcmp(a, uccat_name[i])==0)
				{
					ucd[ic].uccat = i;
					break;
				}
		}

		// Field 4: Bidirectional Category
		ucd[ic].bidicat = -1;
		if (string_get_field(line, ";", 4, a))
		if (strlen(a) > 0)
		{
			for (i=0; i < sizeof(bidicat_name)/sizeof(*bidicat_name); i++)
				if (strcmp(a, bidicat_name[i])==0)
				{
					ucd[ic].bidicat = i;
					break;
				}
		}

		// Field 5: Character Decomposition Mapping
		ucd[ic].decomp_type = -1;
		if (string_get_field(line, ";", 5, a))
		if (strlen(a) > 0)
		{
			strcpy(b, a);
			p = strstr(b, ">");
			if (p)				// if a <> decomposition map type tag was found
			{
				p[1] = '\0';		// end the string b after the >

				for (i=0; i < sizeof(decomp_name)/sizeof(*decomp_name); i++)
					if (strcmp(b, decomp_name[i])==0)
					{
						ucd[ic].decomp_type = i;
						break;
					}

				p = &p[2];		// move p to the start of the first codepoint
			}
			else				// if the decomposition is canonical
			{
				ucd[ic].decomp_type = decomp_canonical;
				p = b;
			}

			sscanf(p, "%x %x", &ucd[ic].combo1, &ucd[ic].combo2);
		}

		// Field 12: Uppercase Mapping
		if (string_get_field(line, ";", 12, a))
		if (strlen(a) > 0)
			sscanf(a, "%x", &ucd[ic].upper_map);

		// Field 13: Lowercase Mapping
		if (string_get_field(line, ";", 13, a))
		if (strlen(a) > 0)
			sscanf(a, "%x", &ucd[ic].lower_map);

		if (strstr(ucd[ic].name, "Last"))		// if the name contains Last it means it's the end of a range
		{
			p = strstr(ucd[ic-1].name, ", First");	// edit the name of the range
			if (p)
			{
				p[0] = '>';
				p[1] = '\0';
			}

			for (i=ucd[ic-1].codepoint+1; i < ucd[ic].codepoint; i++)	// refer all codepoints in the LUT to the first entry
				(*codepoint_lut)[i] = ic-1;
		}

		ic++;
	}

	fclose (udf);

	return ucd;
}


void init_unicode_data()
{
	/*if (unicode_data)
		return ;

	unicode_data = load_unicode_data_from_file("../exp/unicode/UnicodeData.txt", &codepoint_lut);*/

	int i, ic;

	if (codepoint_lut)
		return ;

	codepoint_lut = calloc (0x110000, sizeof(int16_t));

	for (ic=0; ic < sizeof(unicode_data)/sizeof(*unicode_data); ic++)
	{
		codepoint_lut[unicode_data[ic].codepoint] = ic;	// put the table ID into the LUT taking codepoints as index

		if (unicode_data[ic].name)
			if (strstr(unicode_data[ic].name, "Last"))		// if the name contains Last it means it's the end of a range
			{
				for (i=unicode_data[ic-1].codepoint+1; i < unicode_data[ic].codepoint; i++)	// refer all codepoints in the LUT to the first entry
					codepoint_lut[i] = ic-1;
			}
	}
}

unicode_data_t get_unicode_data(uint32_t c)
{
	init_unicode_data();

	c = MINN(c, 0x10FFFF);

	return unicode_data[codepoint_lut[c]];
}

void make_unicode_data_table_file()	// generates the unicode_data_table.h file
{
	int i, end;
	FILE *file;
	unicode_data_t *ucd, e;

	ucd = load_unicode_data_from_file("../exp/unicode/UnicodeData.txt", &codepoint_lut);

	file = fopen_utf8("../rouziclib/text/unicode_data_table.h", "wb");

	fprintf(file, "// Generated by function make_unicode_data_table_file()\nconst unicode_data_t unicode_data[] = {\n");

	for (i=0, end=codepoint_lut[0x10FFFD]; i <= end; i++)
	{
		e = ucd[i];
		fprintf(file, "{ 0x%04X, \"%s\", %d, %d, %d, ", e.codepoint, e.name, e.uccat, e.bidicat, e.decomp_type);
		fprintf(file, e.combo1 ? "0x%04X, " : "0, ", e.combo1);
		fprintf(file, e.combo2 ? "0x%04X, " : "0, ", e.combo2);
		fprintf(file, e.upper_map ? "0x%04X, " : "0, ", e.upper_map);
		fprintf(file, e.lower_map ? "0x%04X }" : "0 }", e.lower_map);
		fprintf(file, i==end ? " };" : ",\n");
	}

	fclose (file);
}
