// in general/structs.h:
// buffer_t

extern char *vbufprintf(buffer_t *s, const char *format, va_list args);
extern char *bufprintf(buffer_t *s, const char *format, ...);
extern char *bufnprintf(buffer_t *s, size_t n, const char *format, ...);
extern char *bufwrite(buffer_t *s, uint8_t *ptr, size_t size);
extern void buf_alloc_enough(buffer_t *s, size_t req_size);
extern void free_buf(buffer_t *s);
extern void clear_buf(buffer_t *s);
extern buffer_t *append_buf(buffer_t *a, buffer_t *b);
extern buffer_t buf_copy_part(buffer_t src, size_t start, size_t len);

extern void buf_remove_first_bytes(buffer_t *s, size_t n);
extern int buf_tail(buffer_t *s, int n);
extern void bufprint_gmtime(buffer_t *s, time_t t);
extern buffer_t buf_load_raw_file(const char *path);
extern buffer_t buf_load_raw_file_dos_conv(const char *path);
extern int buf_save_raw_file(buffer_t *s, const char *path, const char *mode);
