// taken from SDL2's include/SDL_scancode.h which itself comes from the USB HID usage tables https://usb.org/sites/default/files/documents/hut1_12v2.pdf

enum
{
	RL_SCANCODE_UNKNOWN = 0,

	/**
	 *  \name Usage page 0x07
	 *
	 *  These values are from usage page 0x07 (USB keyboard page).
	 */
	/* @{ */

	RL_SCANCODE_A = 4,
	RL_SCANCODE_B = 5,
	RL_SCANCODE_C = 6,
	RL_SCANCODE_D = 7,
	RL_SCANCODE_E = 8,
	RL_SCANCODE_F = 9,
	RL_SCANCODE_G = 10,
	RL_SCANCODE_H = 11,
	RL_SCANCODE_I = 12,
	RL_SCANCODE_J = 13,
	RL_SCANCODE_K = 14,
	RL_SCANCODE_L = 15,
	RL_SCANCODE_M = 16,
	RL_SCANCODE_N = 17,
	RL_SCANCODE_O = 18,
	RL_SCANCODE_P = 19,
	RL_SCANCODE_Q = 20,
	RL_SCANCODE_R = 21,
	RL_SCANCODE_S = 22,
	RL_SCANCODE_T = 23,
	RL_SCANCODE_U = 24,
	RL_SCANCODE_V = 25,
	RL_SCANCODE_W = 26,
	RL_SCANCODE_X = 27,
	RL_SCANCODE_Y = 28,
	RL_SCANCODE_Z = 29,

	RL_SCANCODE_1 = 30,
	RL_SCANCODE_2 = 31,
	RL_SCANCODE_3 = 32,
	RL_SCANCODE_4 = 33,
	RL_SCANCODE_5 = 34,
	RL_SCANCODE_6 = 35,
	RL_SCANCODE_7 = 36,
	RL_SCANCODE_8 = 37,
	RL_SCANCODE_9 = 38,
	RL_SCANCODE_0 = 39,

	RL_SCANCODE_RETURN = 40,
	RL_SCANCODE_ESCAPE = 41,
	RL_SCANCODE_BACKSPACE = 42,
	RL_SCANCODE_TAB = 43,
	RL_SCANCODE_SPACE = 44,

	RL_SCANCODE_MINUS = 45,
	RL_SCANCODE_EQUALS = 46,
	RL_SCANCODE_LEFTBRACKET = 47,
	RL_SCANCODE_RIGHTBRACKET = 48,
	RL_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
				      *   key on ISO keyboards and at the right end
				      *   of the QWERTY row on ANSI keyboards.
				      *   Produces REVERSE SOLIDUS (backslash) and
				      *   VERTICAL LINE in a US layout, REVERSE
				      *   SOLIDUS and VERTICAL LINE in a UK Mac
				      *   layout, NUMBER SIGN and TILDE in a UK
				      *   Windows layout, DOLLAR SIGN and POUND SIGN
				      *   in a Swiss German layout, NUMBER SIGN and
				      *   APOSTROPHE in a German layout, GRAVE
				      *   ACCENT and POUND SIGN in a French Mac
				      *   layout, and ASTERISK and MICRO SIGN in a
				      *   French Windows layout.
				      */
	RL_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
				      *   instead of 49 for the same key, but all
				      *   OSes I've seen treat the two codes
				      *   identically. So, as an implementor, unless
				      *   your keyboard generates both of those
				      *   codes and your OS treats them differently,
				      *   you should generate RL_SCANCODE_BACKSLASH
				      *   instead of this code. As a user, you
				      *   should not rely on this code because RL
				      *   will never generate it with most (all?)
				      *   keyboards.
				      */
	RL_SCANCODE_SEMICOLON = 51,
	RL_SCANCODE_APOSTROPHE = 52,
	RL_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
				  *   and ISO keyboards). Produces GRAVE ACCENT and
				  *   TILDE in a US Windows layout and in US and UK
				  *   Mac layouts on ANSI keyboards, GRAVE ACCENT
				  *   and NOT SIGN in a UK Windows layout, SECTION
				  *   SIGN and PLUS-MINUS SIGN in US and UK Mac
				  *   layouts on ISO keyboards, SECTION SIGN and
				  *   DEGREE SIGN in a Swiss German layout (Mac:
				  *   only on ISO keyboards), CIRCUMFLEX ACCENT and
				  *   DEGREE SIGN in a German layout (Mac: only on
				  *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
				  *   French Windows layout, COMMERCIAL AT and
				  *   NUMBER SIGN in a French Mac layout on ISO
				  *   keyboards, and LESS-THAN SIGN and GREATER-THAN
				  *   SIGN in a Swiss German, German, or French Mac
				  *   layout on ANSI keyboards.
				  */
	RL_SCANCODE_COMMA = 54,
	RL_SCANCODE_PERIOD = 55,
	RL_SCANCODE_SLASH = 56,

	RL_SCANCODE_CAPSLOCK = 57,

	RL_SCANCODE_F1 = 58,
	RL_SCANCODE_F2 = 59,
	RL_SCANCODE_F3 = 60,
	RL_SCANCODE_F4 = 61,
	RL_SCANCODE_F5 = 62,
	RL_SCANCODE_F6 = 63,
	RL_SCANCODE_F7 = 64,
	RL_SCANCODE_F8 = 65,
	RL_SCANCODE_F9 = 66,
	RL_SCANCODE_F10 = 67,
	RL_SCANCODE_F11 = 68,
	RL_SCANCODE_F12 = 69,

	RL_SCANCODE_PRINTSCREEN = 70,
	RL_SCANCODE_SCROLLLOCK = 71,
	RL_SCANCODE_PAUSE = 72,
	RL_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
				    does send code 73, not 117) */
	RL_SCANCODE_HOME = 74,
	RL_SCANCODE_PAGEUP = 75,
	RL_SCANCODE_DELETE = 76,
	RL_SCANCODE_END = 77,
	RL_SCANCODE_PAGEDOWN = 78,
	RL_SCANCODE_RIGHT = 79,
	RL_SCANCODE_LEFT = 80,
	RL_SCANCODE_DOWN = 81,
	RL_SCANCODE_UP = 82,

	RL_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
	*/
	RL_SCANCODE_KP_DIVIDE = 84,
	RL_SCANCODE_KP_MULTIPLY = 85,
	RL_SCANCODE_KP_MINUS = 86,
	RL_SCANCODE_KP_PLUS = 87,
	RL_SCANCODE_KP_ENTER = 88,
	RL_SCANCODE_KP_1 = 89,
	RL_SCANCODE_KP_2 = 90,
	RL_SCANCODE_KP_3 = 91,
	RL_SCANCODE_KP_4 = 92,
	RL_SCANCODE_KP_5 = 93,
	RL_SCANCODE_KP_6 = 94,
	RL_SCANCODE_KP_7 = 95,
	RL_SCANCODE_KP_8 = 96,
	RL_SCANCODE_KP_9 = 97,
	RL_SCANCODE_KP_0 = 98,
	RL_SCANCODE_KP_PERIOD = 99,

	RL_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
					    *   keyboards have over ANSI ones,
					    *   located between left shift and Y.
					    *   Produces GRAVE ACCENT and TILDE in a
					    *   US or UK Mac layout, REVERSE SOLIDUS
					    *   (backslash) and VERTICAL LINE in a
					    *   US or UK Windows layout, and
					    *   LESS-THAN SIGN and GREATER-THAN SIGN
					    *   in a Swiss German, German, or French
					    *   layout. */
	RL_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
	RL_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
				   *   not a physical key - but some Mac keyboards
				   *   do have a power key. */
	RL_SCANCODE_KP_EQUALS = 103,
	RL_SCANCODE_F13 = 104,
	RL_SCANCODE_F14 = 105,
	RL_SCANCODE_F15 = 106,
	RL_SCANCODE_F16 = 107,
	RL_SCANCODE_F17 = 108,
	RL_SCANCODE_F18 = 109,
	RL_SCANCODE_F19 = 110,
	RL_SCANCODE_F20 = 111,
	RL_SCANCODE_F21 = 112,
	RL_SCANCODE_F22 = 113,
	RL_SCANCODE_F23 = 114,
	RL_SCANCODE_F24 = 115,
	RL_SCANCODE_EXECUTE = 116,
	RL_SCANCODE_HELP = 117,
	RL_SCANCODE_MENU = 118,
	RL_SCANCODE_SELECT = 119,
	RL_SCANCODE_STOP = 120,
	RL_SCANCODE_AGAIN = 121,   /**< redo */
	RL_SCANCODE_UNDO = 122,
	RL_SCANCODE_CUT = 123,
	RL_SCANCODE_COPY = 124,
	RL_SCANCODE_PASTE = 125,
	RL_SCANCODE_FIND = 126,
	RL_SCANCODE_MUTE = 127,
	RL_SCANCODE_VOLUMEUP = 128,
	RL_SCANCODE_VOLUMEDOWN = 129,
	/* not sure whether there's a reason to enable these */
	/*     RL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
	/*     RL_SCANCODE_LOCKINGNUMLOCK = 131, */
	/*     RL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
	RL_SCANCODE_KP_COMMA = 133,
	RL_SCANCODE_KP_EQUALSAS400 = 134,

	RL_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
					     footnotes in USB doc */
	RL_SCANCODE_INTERNATIONAL2 = 136,
	RL_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
	RL_SCANCODE_INTERNATIONAL4 = 138,
	RL_SCANCODE_INTERNATIONAL5 = 139,
	RL_SCANCODE_INTERNATIONAL6 = 140,
	RL_SCANCODE_INTERNATIONAL7 = 141,
	RL_SCANCODE_INTERNATIONAL8 = 142,
	RL_SCANCODE_INTERNATIONAL9 = 143,
	RL_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
	RL_SCANCODE_LANG2 = 145, /**< Hanja conversion */
	RL_SCANCODE_LANG3 = 146, /**< Katakana */
	RL_SCANCODE_LANG4 = 147, /**< Hiragana */
	RL_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
	RL_SCANCODE_LANG6 = 149, /**< reserved */
	RL_SCANCODE_LANG7 = 150, /**< reserved */
	RL_SCANCODE_LANG8 = 151, /**< reserved */
	RL_SCANCODE_LANG9 = 152, /**< reserved */

	RL_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
	RL_SCANCODE_SYSREQ = 154,
	RL_SCANCODE_CANCEL = 155,
	RL_SCANCODE_CLEAR = 156,
	RL_SCANCODE_PRIOR = 157,
	RL_SCANCODE_RETURN2 = 158,
	RL_SCANCODE_SEPARATOR = 159,
	RL_SCANCODE_OUT = 160,
	RL_SCANCODE_OPER = 161,
	RL_SCANCODE_CLEARAGAIN = 162,
	RL_SCANCODE_CRSEL = 163,
	RL_SCANCODE_EXSEL = 164,

	RL_SCANCODE_KP_00 = 176,
	RL_SCANCODE_KP_000 = 177,
	RL_SCANCODE_THOUSANDSSEPARATOR = 178,
	RL_SCANCODE_DECIMALSEPARATOR = 179,
	RL_SCANCODE_CURRENCYUNIT = 180,
	RL_SCANCODE_CURRENCYSUBUNIT = 181,
	RL_SCANCODE_KP_LEFTPAREN = 182,
	RL_SCANCODE_KP_RIGHTPAREN = 183,
	RL_SCANCODE_KP_LEFTBRACE = 184,
	RL_SCANCODE_KP_RIGHTBRACE = 185,
	RL_SCANCODE_KP_TAB = 186,
	RL_SCANCODE_KP_BACKSPACE = 187,
	RL_SCANCODE_KP_A = 188,
	RL_SCANCODE_KP_B = 189,
	RL_SCANCODE_KP_C = 190,
	RL_SCANCODE_KP_D = 191,
	RL_SCANCODE_KP_E = 192,
	RL_SCANCODE_KP_F = 193,
	RL_SCANCODE_KP_XOR = 194,
	RL_SCANCODE_KP_POWER = 195,
	RL_SCANCODE_KP_PERCENT = 196,
	RL_SCANCODE_KP_LESS = 197,
	RL_SCANCODE_KP_GREATER = 198,
	RL_SCANCODE_KP_AMPERSAND = 199,
	RL_SCANCODE_KP_DBLAMPERSAND = 200,
	RL_SCANCODE_KP_VERTICALBAR = 201,
	RL_SCANCODE_KP_DBLVERTICALBAR = 202,
	RL_SCANCODE_KP_COLON = 203,
	RL_SCANCODE_KP_HASH = 204,
	RL_SCANCODE_KP_SPACE = 205,
	RL_SCANCODE_KP_AT = 206,
	RL_SCANCODE_KP_EXCLAM = 207,
	RL_SCANCODE_KP_MEMSTORE = 208,
	RL_SCANCODE_KP_MEMRECALL = 209,
	RL_SCANCODE_KP_MEMCLEAR = 210,
	RL_SCANCODE_KP_MEMADD = 211,
	RL_SCANCODE_KP_MEMSUBTRACT = 212,
	RL_SCANCODE_KP_MEMMULTIPLY = 213,
	RL_SCANCODE_KP_MEMDIVIDE = 214,
	RL_SCANCODE_KP_PLUSMINUS = 215,
	RL_SCANCODE_KP_CLEAR = 216,
	RL_SCANCODE_KP_CLEARENTRY = 217,
	RL_SCANCODE_KP_BINARY = 218,
	RL_SCANCODE_KP_OCTAL = 219,
	RL_SCANCODE_KP_DECIMAL = 220,
	RL_SCANCODE_KP_HEXADECIMAL = 221,

	RL_SCANCODE_LCTRL = 224,
	RL_SCANCODE_LSHIFT = 225,
	RL_SCANCODE_LALT = 226, /**< alt, option */
	RL_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
	RL_SCANCODE_RCTRL = 228,
	RL_SCANCODE_RSHIFT = 229,
	RL_SCANCODE_RALT = 230, /**< alt gr, option */
	RL_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

	RL_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
				     *   by any of the above, but since there's a
				     *   special KMOD_MODE for it I'm adding it here
				     */

	/* @} *//* Usage page 0x07 */

	/**
	 *  \name Usage page 0x0C
	 *
	 *  These values are mapped from usage page 0x0C (USB consumer page).
	 */
	/* @{ */

	RL_SCANCODE_AUDIONEXT = 258,
	RL_SCANCODE_AUDIOPREV = 259,
	RL_SCANCODE_AUDIOSTOP = 260,
	RL_SCANCODE_AUDIOPLAY = 261,
	RL_SCANCODE_AUDIOMUTE = 262,
	RL_SCANCODE_MEDIASELECT = 263,
	RL_SCANCODE_WWW = 264,
	RL_SCANCODE_MAIL = 265,
	RL_SCANCODE_CALCULATOR = 266,
	RL_SCANCODE_COMPUTER = 267,
	RL_SCANCODE_AC_SEARCH = 268,
	RL_SCANCODE_AC_HOME = 269,
	RL_SCANCODE_AC_BACK = 270,
	RL_SCANCODE_AC_FORWARD = 271,
	RL_SCANCODE_AC_STOP = 272,
	RL_SCANCODE_AC_REFRESH = 273,
	RL_SCANCODE_AC_BOOKMARKS = 274,

	/* @} *//* Usage page 0x0C */

	/**
	 *  \name Walther keys
	 *
	 *  These are values that Christian Walther added (for mac keyboard?).
	 */
	/* @{ */

	RL_SCANCODE_BRIGHTNESSDOWN = 275,
	RL_SCANCODE_BRIGHTNESSUP = 276,
	RL_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
					    switch, video mode switch */
	RL_SCANCODE_KBDILLUMTOGGLE = 278,
	RL_SCANCODE_KBDILLUMDOWN = 279,
	RL_SCANCODE_KBDILLUMUP = 280,
	RL_SCANCODE_EJECT = 281,
	RL_SCANCODE_SLEEP = 282,

	RL_SCANCODE_APP1 = 283,
	RL_SCANCODE_APP2 = 284,

	/* @} *//* Walther keys */

	/**
	 *  \name Usage page 0x0C (additional media keys)
	 *
	 *  These values are mapped from usage page 0x0C (USB consumer page).
	 */
	/* @{ */

	RL_SCANCODE_AUDIOREWIND = 285,
	RL_SCANCODE_AUDIOFASTFORWARD = 286,

	/* @} *//* Usage page 0x0C (additional media keys) */

	/* Add any other keys here. */

	RL_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
				  for array bounds */
};
