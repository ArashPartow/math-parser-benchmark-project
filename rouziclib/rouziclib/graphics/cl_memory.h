// in graphics/graphics_struct.h:
// cl_data_alloc_t

extern void cl_copy_buffer_to_device(void *buffer, size_t offset, size_t size);
extern void cl_copy_raster_to_device(raster_t r, size_t offset);
extern void data_cl_alloc(int mb);
extern void data_cl_realloc(ssize_t buffer_size);
extern void cl_data_table_remove_entry(int i);
extern void cl_data_table_prune_unused();
extern void cl_data_table_remove_entry_by_host_ptr(void *host_ptr);
extern uint64_t cl_add_data_table_entry(size_t *table_index, size_t prev_end, void *buffer, size_t size, int *table_index_p);
extern void cl_data_find_max_free_space();
extern int cl_data_check_enough_room(size_t align_size, size_t buffer_size);

extern uint64_t cl_add_buffer_to_data_table(void *buffer, size_t buffer_size, size_t align_size, int *table_index);
extern uint64_t cl_add_raster_to_data_table(raster_t *r);
