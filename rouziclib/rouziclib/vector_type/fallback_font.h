const char *fallback_font[] = {
"glyph ' '",
"	bounds -1 1",

"glyph '!'",
"	copy '.'",
"	p1	0	6",
"	p2	0	2",
"	lines p1 p2",

"glyph '\"'",
"	rect	p1	-0;6 4;6	0;6 6",
"	lines p1 p3",
"	lines p2 p4",

"glyph '#'",
"	copy '\"'",
"	scale	1;4 2;8	0 6.6",
"	copy '='",
"	shearX	0;4	0 3",

"glyph '$'",
"	copy 'S'",
"	p1	0	7",
"	p2	0	-1",
"	lines p1 p2",

"glyph '%'",
"	subglyph .",
"	copy '.'",
"	scale 2",
"	subend",

"	p1	-2	0;6",
"	p2	2	5;6",
"	lines p1 p2",
"	copy '%' .",
"	move last -1	3;6",
"	copy '%' .",
"	move last 1	0;6",

"glyph '&'",
"	p1	2	0",
"	p2	-1;4	4;8",
"	p3	-1;4	6",
"	p4	0;7	6",
"	p5	0;7	4;8",
"	p6	-2	2;6",
"	p7	-2	0",
"	p8	0	0",
"	p9	2	2",
"	lines p1 to p9",

"glyph '''",
"	p1	0	6",
"	p2	0	4;6",
"	lines p1 p2",

"glyph '('",
"	p1	0;8	6",
"	p2	-0;8	4;8",
"	mirror	h 3	p1 p2	p3",
"	lines p1 p2 p4 p3",

"glyph ')'",
"	copy '('",
"	scale	-1	1",

"glyph '*'",
"	circle	p1 p6	6 1;5	0 4;4	0",
"	lines p1 p4",
"	lines p2 p5",
"	lines p3 p6",

"glyph '+'",
"	copy '|'",
"	scale 0;6 0;6	0 3",
"	copy '-'",

"glyph ','",
"	p1	0;3	0;6",
"	p2	-0;6	-1",
"	lines p1 p2",

"glyph '-'",
"	p1	-1;6	3",
"	p2	1;6	3",
"	lines p1 p2",

"glyph '.'",
"	p1	0	0",
"	p2	-0;6	0;6",
"	p3	0	1",
"	p4	0;6	0;6",
"	lines p1 to p4 p1",

"glyph '/'",
"	p1	-1;6	0",
"	p2	1;6	6",
"	lines p1 p2",

"glyph '0'",
"	copy 'O'",
"	p1	2	5",
"	p2	-2	1",
"	lines p1 p2",

"glyph '1'",
"	copy '|'",

"glyph '2'",
"	rect	p1	-2 3	2 6",
"	rect	p5	-2 0	2 1",
"	lines	p3 p4 p2 p1 p5 p6",

"glyph '3'",
"	copy 'E'",
"	scale	-1 1",

"glyph '4'",
"	p1	1	0",
"	p2	1	6",
"	p3	-2	2",
"	p4	2	2",
"	lines p1 to p4",

"glyph '5'",
"	copy '2'",
"	scale	-1 1",

"glyph '6'",
"	rect	p1	-2 3	2 6",
"	rect	p5	-2 0	2 1",
"	lines	p4 p3 p5 p6 p2 p1",

"glyph '7'",
"	p1	-2	6",
"	p2	2	6",
"	p3	-1	0",
"	lines p1 p2 p3",

"glyph '8'",
"	copy '_'",
"	move 0 3",
"	copy 'O'",

"glyph '9'",
"	copy '6'",
"	scale	-1 -1	0 3",

"glyph ':'",
"	copy '.'",
"	move 0 2;6",
"	copy '.'",

"glyph ';'",
"	copy '.'",
"	move 0 2;6",
"	copy ','",

"glyph '<'",
"	p1	1;6	0;6",
"	p2	-1;6	3",
"	p3	1;6	5;6",
"	lines p1 p2 p3",

"glyph '='",
"	rect	p1	-1;6 2;3	1;6 3;9",
"	lines p1 p2",
"	lines p3 p4",

"glyph '>'",
"	copy '<'",
"	scale	-1	1",

"glyph '?'",
"	copy '.'",
"	p1	-1;4	4;8",
"	p2	-0	6",
"	p3	1;4	4;8",
"	p4	0	3;4",
"	p5	0	2;3",
"	lines p1 to p5",

"glyph '@'",
"	rect	p1	-1;3 0;6	1;3 4",
"	p5	3	0;6",
"	rect	p6	-3 -1;6	3 6",
"	lines p2 p4 p3 p1 p5 p9 p8 p6 p7",

"glyph 'A'",
"	copy 'V'",
"	scale	-1 -1	0 3",
"	copy '-'",
"	scale last 0;9;7",

"glyph 'B'",
"	rect	p1	-2 3	1 6",
"	rect	p5	-2 0	2 3",
"	lines p2 p4 p3 p5 p6 p8 p7",

"glyph 'C'",
"	rect	p1	-2 0	2 6",
"	lines p4 p3 p1 p2",

"glyph 'D'",
"	p1	-2	6",
"	p2	0	6",
"	p3	2	4",
"	mirror	h 3	p1 p3	p4",
"	lines p1 p2 p3 p6 p5 p4 p1",

"glyph 'E'",
"	copy 'F'",
"	copy '_'",

"glyph 'F'",
"	copy '-'",
"	move	-0;6",
"	copy 'L'",
"	scale	1 -1	0 3",

"glyph 'G'",
"	copy 'C'",
"	p1	2	3",
"	p2	0	3",
"	lines p-2 p1 p2",

"glyph 'H'",
"	copy '_'",
"	move 0 3",
"	rect	p1	-2 0	2 6",
"	lines p1 p3",
"	lines p2 p4",

"glyph 'I'",
"	copy 'H'",
"	rotate	3	0 3",
"	scale	0;4 1;6	0 3",

"glyph 'J'",
"	copy 'U'",
"	p-1	-2	2",

"glyph 'K'",
"	copy '|'",
"	move -1;6",
"	copy '<'",
"	scale last	1 1.2	0 3",

"glyph 'L'",
"	rect	p1	-2 0	2 6",
"	lines p3 p1 p2",
"	bounds -2 1;6",

"glyph 'M'",
"	rect	p1	-2 0	2 6",
"	p5	0	2",
"	lines p1 p3 p5 p4 p2",

"glyph 'N'",
"	rect	p1	-2 0	2 6",
"	lines p1 p3 p2 p4",

"glyph 'O'",
"	rect	p1	-2 0	2 6",
"	lines p1 p2 p4 p3 p1",

"glyph 'P'",
"	copy '|'",
"	move -2",
"	rect	p1	-2 3	2 6",
"	lines p3 p4 p2 p1",

"glyph 'Q'",
"	copy 'O'",
"	p1	0	2",
"	p2	2;6	-0;6",
"	lines p1 p2",
"	bounds -2 2",

"glyph 'R'",
"	copy 'P'",
"	p1	0	3",
"	p2	2	0",
"	lines p1 p2",

"glyph 'S'",
"	copy '5'",

"glyph 'T'",
"	copy '_'",
"	copy '|'",
"	scale	1 -1	0 3",
"	bounds -1;6 1;6",

"glyph 'U'",
"	rect	p1	-2 0	2 6",
"	lines p3 p1 p2 p4",

"glyph 'V'",
"	p1	-2	6",
"	p2	0	0",
"	p3	2	6",
"	lines p1 p2 p3",
"	bounds -1;6 1;6",

"glyph 'W'",
"	p1	-2	6",
"	p2	-1	0",
"	p3	0	3",
"	mirror	v0	p1 p2	p4",
"	lines p1 p2 p3 p5 p4",

"glyph 'X'",
"	rect	p1	-2 0	2 6",
"	lines p1 p4",
"	lines p2 p3",

"glyph 'Y'",
"	copy 'V'",
"	move	0 6",
"	copy '|'",
"	scale	1 0;6",

"glyph 'Z'",
"	rect	p1	-2 0	2 6",
"	lines p3 p4 p1 p2",

"glyph '['",
"	copy ']'",
"	scale	-1	1",

"glyph '\\'",
"	copy '/'",
"	scale	-1	1",

"glyph ']'",
"	rect	p1	-0;8 0	0;8 6",
"	lines p1 p2 p4 p3",

"glyph '_'",
"	p1	-2	0",
"	p2	2	0",
"	lines p1 p2",

"glyph '`'",
"	p1	-0;6	6",
"	p2	0;6	4;6",
"	lines p1 p2",

"glyph '|'",
"	p1	0	0",
"	p2	0	6",
"	lines p1 p2",

"glyph 00B0",
"	circle p1 p8	8  0;8	0 5;8	-0;9",
"	lines p1 to p8 p1",

"glyph 2610",
"	rect	p1	-3 0	3 6",
"	lines p1 p2 p4 p3 p1",

"glyph 2611",
"	copy 2610",
"	p1	-1;3	3",
"	p2	-0;3	2",
"	p3	1;3	4;6",
"	lines p1 p2 p3",
"	scale loc	1;6 1;6	0 3",

"glyph F2612",
"	copy 2610",
"	copy '-'",

"glyph F003A",
"	copy '1'",
"	move -3;6 0",
"	copy '0'",
"	move 1;3 0",

"glyph F003B",
"	copy '1'",
"	move -3 0",
"	copy '1'",
"	move 1;6 0",

"glyph F003C",
"	copy '1'",
"	move -3;6 0",
"	copy '2'",
"	move 1;3 0",

"glyph 1F4CC",
"	p1	0	-0;3",
"	p2	0;3	0;3",
"	p3	0;3	2;6",
"	p4	2;2	2;6",
"	p5	2	3",
"	p6	1	3;6",
"	p7	0;10	4;10",
"	p8	1;4	5",
"	p9	1;2	5;9",
"	mirror	v 0	p1 p9	p10",
"	lines p1 to p9 p18 to p10",
"	lines p3 p12",
"	move	0	0;3",

"glyph F0100",
"	p1	0	5",
"	p2	0	0",
"	p3	5	0",
"	p4	4	1",
"	p5	1	1",
"	p6	1	4",
"	lines p1 to p6 p1",
"	rotate	-1;6",
"	scale	0;9",
"	move	0	1;4",

"glyph 2714",
"	p1	0	3",
"	p2	0	0",
"	p3	5	0",
"	p4	5	1;2",
"	p5	1;2	1;2",
"	p6	1;2	3",
"	lines p1 to p6 p1",
"	rotate	-1;6",
"	move	0	1",

"glyph 2A09",
"	p1	-3	6",
"	p2	3	0",
"	p3	-3	0",
"	p4	3	6",
"	lines p1 p2",
"	lines p3 p4",
"	bounds	-2;6	2;6",

"glyph E010", 
"	bounds 0 0", 
 
"glyph E011", 
"	bounds 0 1", 
 
"glyph E012", 
"	bounds 0 2", 
 
"glyph E013", 
"	bounds 0 3", 
 
"glyph E014", 
"	bounds 0 4", 
 
"glyph E015", 
"	bounds 0 5", 
 
"glyph E016", 
"	bounds 0 6", 
 
"glyph E017", 
"	bounds 0 7", 
 
"glyph E018", 
"	bounds 0 8", 
 
"glyph E019", 
"	bounds 0 9", 
 
"glyph E01A", 
"	bounds 0 10", 
 
"glyph E01B", 
"	bounds 0 11", 
 
"glyph E01C", 
"	bounds 0 12", 
 
"glyph E01D", 
"	bounds 0 0;1", 
 
"glyph E01E", 
"	bounds 0 0;2", 
 
"glyph E01F", 
"	bounds 0 0;3", 
 
"glyph E020", 
"	bounds 0 0;4", 
 
"glyph E021", 
"	bounds 0 0;5", 
 
"glyph E022", 
"	bounds 0 0;6", 
 
"glyph E023", 
"	bounds 0 24", 
 
"glyph E024", 
"	bounds 0 36", 
 
"glyph E025", 
"	bounds 0 48", 
 
"glyph E026", 
"	bounds 0 60", 
 
"glyph E027", 
"	bounds 0 72", 
 
"glyph E028", 
"	bounds 0 84", 
 
"glyph E029", 
"	bounds 0 96", 
 
"glyph E02A", 
"	bounds 0 108", 
 
"glyph E02B", 
"	bounds 0 120", 
 
"glyph E02C", 
"	bounds 0 240", 
 
"glyph E02D", 
"	bounds 0 360", 
 
"glyph E02E", 
"	bounds 0 480", 
 
"glyph E02F", 
"	bounds 0 600", 

};
