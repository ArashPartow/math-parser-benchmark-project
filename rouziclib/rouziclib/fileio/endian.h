#ifndef RL_DONT_ASSUME_LITTLE_ENDIAN
#define ASS_LE
#endif

// Read and write to a file
extern uint8_t fread_byte8(FILE *file);
extern uint16_t fread_LE16(FILE *file);
extern uint16_t fread_BE16(FILE *file);
extern uint32_t fread_LE32(FILE *file);
extern uint32_t fread_BE32(FILE *file);
extern uint64_t fread_LE64(FILE *file);
extern uint64_t fread_BE64(FILE *file);
extern void fwrite_byte8(FILE *file, uint8_t s);
extern void fwrite_LE16(FILE *file, uint16_t s);
extern void fwrite_BE16(FILE *file, uint16_t s);
extern void fwrite_LE32(FILE *file, uint32_t w);
extern void fwrite_BE32(FILE *file, uint32_t w);
extern void fwrite_LE64(FILE *file, uint64_t w);
extern void fwrite_BE64(FILE *file, uint64_t w);


// Read from a buffer
extern uint8_t read_byte8(const void *ptr, size_t *index);
extern int32_t read_byte8s(const void *ptr, size_t *index);
extern int32_t read_byte8s_offset(const void *ptr, size_t *index);
extern uint16_t read_LE16(const void *ptr, size_t *index);
extern uint16_t read_BE16(const void *ptr, size_t *index);
extern int32_t read_LE16s(const void *ptr, size_t *index);
extern int32_t read_BE16s(const void *ptr, size_t *index);
extern uint32_t read_LE24(const void *ptr, size_t *index);
extern uint32_t read_BE24(const void *ptr, size_t *index);
extern int32_t read_LE24s(const void *ptr, size_t *index);
extern int32_t read_BE24s(const void *ptr, size_t *index);
extern uint32_t read_LE32(const void *ptr, size_t *index);
extern uint32_t read_BE32(const void *ptr, size_t *index);
extern uint64_t read_LE64(const void *ptr, size_t *index);
extern uint64_t read_LEupto64(const void *ptr, size_t *index, size_t size);
extern uint64_t read_BE64(const void *ptr, size_t *index);

// Write to a buffer
extern void print_LE16(uint8_t *buf, uint16_t data);
extern void print_LE24(uint8_t *buf, uint32_t data);
extern void print_LE32(uint8_t *buf, uint32_t data);
extern void print_LE64(uint8_t *buf, uint64_t data);
extern void print_BE16(uint8_t *buf, uint16_t data);
extern void print_BE24(uint8_t *buf, uint32_t data);
extern void print_BE32(uint8_t *buf, uint32_t data);
extern void print_BE64(uint8_t *buf, uint64_t data);

// Like print but increment the pointer
extern void write_byte8(uint8_t **p, uint8_t data);
extern void write_LE16(uint8_t **p, uint16_t data);
extern void write_LE32(uint8_t **p, uint32_t data);
extern void write_LE64(uint8_t **p, uint64_t data);

// Write to generic buffer
extern void bufwrite_byte8(buffer_t *s, uint8_t data);
extern void bufwrite_LEupto64(buffer_t *s, uint64_t data, size_t size);
#define bufwrite_LE16(s, data) bufwrite_LEupto64(s, data, 2)
#define bufwrite_LE32(s, data) bufwrite_LEupto64(s, data, 4)
#define bufwrite_LE64(s, data) bufwrite_LEupto64(s, data, 8)
