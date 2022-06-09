void cl_copy_buffer_to_device(void *buffer, size_t offset, size_t size)
{
	if (size==0)
		return ;

	if (fb.use_drawq==1 && fb.discard==0)
	{
		#ifdef RL_OPENCL
		cl_int ret = clEnqueueWriteBuffer_wrap(fb.clctx.command_queue, fb.data_cl, CL_FALSE, offset, size, buffer, 0, NULL, NULL);
		CL_ERR_NORET("clEnqueueWriteBuffer (in cl_copy_buffer_to_device(), for fb.data_cl)", ret);
		#endif
	}
}

void cl_copy_raster_to_device(raster_t r, size_t offset)
{
	if (r.buf)
		cl_copy_buffer_to_device(r.buf, offset, r.buf_size);
	else if (r.sq)
		cl_copy_buffer_to_device(r.sq, offset, mul_x_by_y_xyi(r.dim)*sizeof(sqrgb_t));
	else if (r.srgb)
		cl_copy_buffer_to_device(r.srgb, offset, mul_x_by_y_xyi(r.dim)*sizeof(srgb_t));
	else if (r.f)
		cl_copy_buffer_to_device(r.f, offset, mul_x_by_y_xyi(r.dim)*sizeof(frgb_t));
}

void data_cl_alloc(int mb)
{
	fb.data_cl_as = mb * 1024*1024;
	fb.data = calloc(fb.data_cl_as, 1);

	#ifdef RL_OPENCL
	if (fb.use_drawq==1)
	{
		cl_int ret;
		fb.data_cl = clCreateBuffer(fb.clctx.context, CL_MEM_READ_WRITE, fb.data_cl_as, NULL, &ret);
		CL_ERR_NORET("clCreateBuffer (in data_cl_alloc(), for fb.data_cl)", ret);
	}
	#endif

	fb.data_alloc_table_count = 0;
	fb.data_alloc_table_as = 128;
	fb.data_alloc_table = calloc(fb.data_alloc_table_as, sizeof(cl_data_alloc_t));
}

void data_cl_realloc(ssize_t buffer_size)
{
	size_t orig_as, new_as;

	// Free device buffer
	#ifdef RL_OPENCL
	cl_int ret;
	if (fb.use_drawq==1)
	{
		ret = clFinish(fb.clctx.command_queue);
		CL_ERR_NORET("clFinish in data_cl_realloc()", ret);

		// free CL buffer
		if (fb.data_cl)
		{
			ret = clReleaseMemObject(fb.data_cl);
			CL_ERR_NORET("clReleaseMemObject (in data_cl_realloc(), for fb.data_cl)", ret);
		}
	}
	#endif

	if (fb.use_drawq==2)
		drawq_soft_finish();

	// Only free the device buffer if requested size is negative
	if (buffer_size < 0)
	{
		#ifdef RL_OPENCL
		memset(&fb.data_cl, 0, sizeof(cl_mem));
		#endif
		fb.data_cl_as = 0;
		free_null(&fb.data);
		return;
	}

	// Calculate the new allocation size
	orig_as = new_as = fb.data_cl_as;
	do
	{
		new_as += (1LL << log2_ffo64(fb.data_cl_as+buffer_size) - (fb.data_cl_as+buffer_size > 200<<20 ? 3 : 2));	// Increment by 33%-50% or 17%-25% above 200 MB
	}
	while (new_as < fb.data_cl_as + buffer_size);

	// Allocate the CL buffer and shrink it if needed
	if (fb.use_drawq==1)
	{
		#ifdef RL_OPENCL
		do
		{
			fb.data_cl = clCreateBuffer(fb.clctx.context, CL_MEM_READ_WRITE, new_as, NULL, &ret);
			if (ret != CL_SUCCESS)			// if it's too much
				new_as -= 8 << 20;		// remove 8 MB
		}
		while (ret != CL_SUCCESS);
		#endif

		if (new_as < fb.data_cl_as)
			fprintf_rl(stderr, "data_cl_realloc() made fb.data_cl smaller, %g MB to %g MB\n", (double) fb.data_cl_as / sq(1024.), (double) new_as / sq(1024.));
	}

	// Resize the local buffer and copy it back
	if (fb.use_drawq)
	{
		alloc_enough(&fb.data, new_as, &fb.data_cl_as, 1, 1.);
		fb.data_cl_as = new_as;
	}

	if (fb.use_drawq==1)
		cl_copy_buffer_to_device(fb.data, 0, MINN(orig_as, fb.data_cl_as));	// enqueue copy of everything

	fb.must_recalc_free_space = 1;

	//fprintf_rl(stdout, "data_cl resized to %g MB\n", (double) fb.data_cl_as / sq(1024.));
}

void cl_data_table_remove_entry(int i)
{
	fb.data_alloc_table_count--;
	memmove(&fb.data_alloc_table[i], &fb.data_alloc_table[i+1], (fb.data_alloc_table_count - i) * sizeof(cl_data_alloc_t));
	fb.must_recalc_free_space = 1;
}

void cl_data_table_prune_unused()
{
	int i;

	// increment .unused in data_cl, remove the unused entries
	for (i = fb.data_alloc_table_count-1; i >= 0; i--)
	{
		fb.data_alloc_table[i].unused++;

		if (fb.data_alloc_table[i].unused >= 2)
			cl_data_table_remove_entry(i);
	}
}

void cl_data_table_remove_entry_by_host_ptr(void *host_ptr)
{
	int i;

	if (host_ptr==NULL)
		return ;

	// find if buffer is already in the table
	for (i=0; i < fb.data_alloc_table_count; i++)
	{
		if (fb.data_alloc_table[i].host_ptr==host_ptr)	// if it's there
		{
			cl_data_table_remove_entry(i);
			return ;
		}
	}
}

uint64_t cl_add_data_table_entry(size_t *table_index, size_t prev_end, void *buffer, size_t size, int *table_index_p)
{
	alloc_enough(&fb.data_alloc_table, fb.data_alloc_table_count+=1, &fb.data_alloc_table_as, sizeof(cl_data_alloc_t), 1.5);

	// Move the entries that follow
	if (*table_index < fb.data_alloc_table_count-1)
		memmove(&fb.data_alloc_table[*table_index+1], &fb.data_alloc_table[*table_index], (fb.data_alloc_table_count-1 - *table_index) * sizeof(cl_data_alloc_t));

	cl_data_alloc_t *entry = &fb.data_alloc_table[*table_index];

	entry->start = prev_end;
	entry->end = entry->start + size;
	entry->unused = 0;
	entry->host_ptr = buffer;
	if (table_index_p)
		*table_index_p = *table_index;

	memcpy(&fb.data[entry->start], buffer, size);		// copy to the host buffer

	return entry->start;
}

hash_table_elem_t *hash_table_get_elem(void *buffer, int hash)
{
	int index, ofi;
	hash_table_t *ht = &fb.hash_table;

	// look for the hash in the table
	index = ht->elem[hash].index;
	if (index >= 0)
		if (fb.data_alloc_table[index].host_ptr==buffer)
			return &ht->elem[hash];

	// look throw the chain in the overflow table
	ofi = ht->elem[hash].next_index;
	while (ofi >= 0)
	{
		index = ht->overflow[ofi].index;

		if (index < 0)
			return NULL;			// if it's the end of the chain and we found nothing

		if (fb.data_alloc_table[index].host_ptr==buffer)
			return &ht->overflow[ofi];

		ofi = ht->overflow[ofi].next_index;
	}

	return NULL;
}

int hash_table_get_index(void *buffer, int hash)
{
	hash_table_elem_t *hte;

	hte = hash_table_get_elem(buffer, hash);
	if (hte==NULL)
		return -1;

	return hte->index;
}

void cl_data_find_max_free_space()
{
	int i;
	ssize_t prev_end=0, space_size, max_size = 0;

	if (fb.data_space_start > fb.data_copy_start)
		cl_copy_buffer_to_device(&fb.data[fb.data_copy_start], fb.data_copy_start, fb.data_space_start - fb.data_copy_start);

	fb.must_recalc_free_space = 0;
	fb.data_space_start = 0;
	fb.data_space_end = 0;

	// Look for the largest space
	for (i=0; i <= fb.data_alloc_table_count; i++)
	{
		if (i == fb.data_alloc_table_count)
			space_size = fb.data_cl_as - prev_end;
		else
			space_size = fb.data_alloc_table[i].start - prev_end;

		if (space_size > max_size)
		{
			max_size = space_size;
			fb.data_space_index = i;
			fb.data_space_start = prev_end;
			if (i == fb.data_alloc_table_count)
				fb.data_space_end = fb.data_cl_as;
			else
				fb.data_space_end = fb.data_alloc_table[i].start;
		}

		if (i < fb.data_alloc_table_count)
			prev_end = next_aligned_offset(fb.data_alloc_table[i].end, 4);
	}

	fb.data_copy_start = fb.data_space_start;
}

int cl_data_check_enough_room(size_t align_size, size_t buffer_size)
{
	return (ssize_t) fb.data_space_end - (ssize_t) next_aligned_offset(fb.data_space_start, align_size) >= (ssize_t) buffer_size;
}

uint64_t cl_add_buffer_to_data_table(void *buffer, size_t buffer_size, size_t align_size, int *table_index)
{
#ifdef RL_OPENCL
	uint64_t ret=0;
	int i, hash;
	const int ht_size = 1 << 16;
	const int ht_mask = ht_size - 1;

	if (buffer_size == 0)
		return 0;

	// check the provided table index
	if (table_index)
	{
		i = *table_index;

		if (i >=0 && i < fb.data_alloc_table_count)
		if (fb.data_alloc_table[i].host_ptr==buffer)	// if it's there
		{
			fb.data_alloc_table[i].unused = 0;	// we just need to indicate it's still in use
			return fb.data_alloc_table[i].start;	// and that's it
		}
	}

	// check hash table
	hash = get_pointer_hash(buffer) & ht_mask;

	if (fb.hash_table.elem==NULL)	// alloc hash table
	{
		fb.hash_table.elem = calloc(ht_size, sizeof(hash_table_elem_t));
		alloc_enough(&fb.hash_table.overflow, 16, &fb.hash_table.overflow_as, sizeof(hash_table_elem_t), 2.);
	}

	// find if buffer is already in the table
	for (i=0; i < fb.data_alloc_table_count; i++)
	{
		if (fb.data_alloc_table[i].host_ptr==buffer)	// if it's there
		{
			if (table_index)
				*table_index = i;

			fb.data_alloc_table[i].unused = 0;	// we just need to indicate it's still in use
			return fb.data_alloc_table[i].start;	// and that's it
		}
	}

	// Add a new entry
	if (fb.must_recalc_free_space)
		cl_data_find_max_free_space();

	for (i=0; i < 2; i++)
	{
		if (cl_data_check_enough_room(align_size, buffer_size))		// if there's enough room in the current space
		{
			ret = cl_add_data_table_entry(&fb.data_space_index, next_aligned_offset(fb.data_space_start, align_size), buffer, buffer_size, table_index);
			fb.data_space_start = fb.data_alloc_table[fb.data_space_index].end;
			fb.data_alloc_table[fb.data_space_index].unused = 0;
			fb.data_space_index++;
			return ret;
		}

		// If there wasn't enough room in this space
		cl_data_find_max_free_space();		// copy the whole block and find a new space

		if (cl_data_check_enough_room(align_size, buffer_size)==0)		// if there's no space large enough
		{
			data_cl_realloc(buffer_size);	// enlarge the buffer
			cl_data_find_max_free_space();

			if (cl_data_check_enough_room(align_size, buffer_size)==0)	// if there's still not enough space
			{
				fprintf_rl(stderr, "cl_add_buffer_to_data_table() couldn't make enough room in data_cl for %g MB buffer\n", (double) buffer_size / sq(1024.));
				return 0;
			}
		}
	}

	return 0;
#else
	return (uint64_t) buffer;
#endif
}

uint64_t cl_add_raster_to_data_table(raster_t *r)
{
	if (r->buf)
		return cl_add_buffer_to_data_table(r->buf, r->buf_size, 4, &r->table_index);

	if (r->sq)
		return cl_add_buffer_to_data_table(r->sq, mul_x_by_y_xyi(r->dim) * sizeof(sqrgb_t), sizeof(sqrgb_t), &r->table_index);

	if (r->srgb)
		return cl_add_buffer_to_data_table(r->srgb, mul_x_by_y_xyi(r->dim) * sizeof(srgb_t), sizeof(srgb_t), &r->table_index);

	if (r->f)
		return cl_add_buffer_to_data_table(r->f, mul_x_by_y_xyi(r->dim) * sizeof(frgb_t), sizeof(frgb_t), &r->table_index);

	if (r->l)
		return cl_add_buffer_to_data_table(r->l, mul_x_by_y_xyi(r->dim) * sizeof(lrgb_t), sizeof(lrgb_t), &r->table_index);

	return 0;
}
