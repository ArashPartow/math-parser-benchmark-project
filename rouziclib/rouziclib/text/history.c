void text_history_add(text_history_t *th, const char *string)
{
	uint64_t hash;
	int create_entry = 1;

	if (th==NULL)
		return ;

	hash = get_string_hash(string);

	if (th->entry==NULL)
		alloc_enough(&th->entry, 8, &th->entry_as, sizeof(text_history_entry_t), 1.);

	if (th->entry_count > 0)
		if (th->entry[th->entry_count-1].hash == hash)
			create_entry = 0;

	if (create_entry)
	{
		alloc_enough(&th->entry, th->entry_count+=1, &th->entry_as, sizeof(text_history_entry_t), 2.);
		th->entry[th->entry_count-1].hash = hash;
		th->entry[th->entry_count-1].string = make_string_copy(string);
	}
}

char *text_history_get_entry(text_history_t *th, int index)
{
	if (th==NULL)
		return NULL;

	if (th->entry==NULL || th->entry_count <= 0)
		return NULL;

	index = MINN(th->entry_count-1, index);

	return th->entry[index].string;
}
