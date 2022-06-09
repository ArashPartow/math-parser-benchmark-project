typedef struct
{
	uint64_t hash;
	char *string;
} text_history_entry_t;

typedef struct
{
	text_history_entry_t *entry;
	int entry_count, entry_as;
} text_history_t;

extern void text_history_add(text_history_t *th, const char *string);
extern char *text_history_get_entry(text_history_t *th, int index);
