typedef struct
{
	// pointers to original array
	char *path;
	uint8_t *data;
	size_t len;
} fileball_subfile_t;

typedef struct
{
	int file_count;
	fileball_subfile_t *file;
	uint8_t *original_array;
} fileball_t;
