seq_selection_t init_seq_selection(const int count)
{
	seq_selection_t sel={0};

	sel.status = calloc(count, sizeof(int8_t));
	sel.status_as = count;
	sel.status_count = count;
	sel.cur_start = -1;
	sel.cur_end = -1;

	return sel;
}

void free_seq_selection(seq_selection_t *sel)
{
	free(sel->status);
	memset(sel, 0, sizeof(seq_selection_t));
}

void seq_selection_click_process(seq_selection_t *sel, int index, int shift, int control)
{
	int i;
	int32_t i0, i1;

	if (sel==NULL)
		return ;
	if (sel->status==NULL || sel->status_as<=0 || sel->status_count<=0)
		return ;

	if (shift==0 && control==0)	// if single click
	{
		// unselect everything and select the one selected if any (index==-1 deselects all)
		memset(sel->status, 0, sel->status_count * sizeof(int8_t));

		if (index >= 0 && index < sel->status_count)
		{
			sel->status[index] = 1;
			sel->cur_start = sel->cur_end = index;
		}
		else
			sel->cur_start = sel->cur_end = -1;
	}
	else if (shift)
	{
		if (sel->cur_start >= 0 && sel->cur_end < sel->status_count)
		{
			if (sel->cur_end >= 0 && sel->cur_end < sel->status_count)
			{
				i0 = sel->cur_start;
				i1 = sel->cur_end;
				minmax_i32(&i0, &i1);

				for (i=i0; i <= i1; i++)
					sel->status[i] = 0;	// unset the old range
			}

			sel->cur_end = rangelimit_i32(index, 0, sel->status_count-1);

			i0 = sel->cur_start;
			i1 = sel->cur_end;
			minmax_i32(&i0, &i1);

			for (i=i0; i <= i1; i++)
				sel->status[i] = 1;	// set the new range
		}
	}
	else	// control key
	{
		if (index >= 0 && index < sel->status_count)
		{
			sel->status[index] ^= 1;
			sel->cur_start = sel->cur_end = index;
		}
	}
}

int seq_selection_sel_count(seq_selection_t *sel)
{
	int i, count=0;

	if (sel==NULL)
		return 0;
	if (sel->status==NULL || sel->status_as<=0 || sel->status_count<=0)
		return 0;

	for (i=0; i < sel->status_count; i++)
		if (sel->status[i])
			count++;

	return count;
}

int seq_selection_find_first(seq_selection_t *sel)
{
	int i;

	if (sel==NULL)
		return -1;
	if (sel->status==NULL || sel->status_as<=0 || sel->status_count<=0)
		return -1;

	for (i=0; i < sel->status_count; i++)
		if (sel->status[i])
			return i;

	return -1;
}

int seq_selection_find_last(seq_selection_t *sel)
{
	int i;

	if (sel==NULL)
		return -1;
	if (sel->status==NULL || sel->status_as<=0 || sel->status_count<=0)
		return -1;

	for (i=sel->status_count-1; i >= 0; i--)
		if (sel->status[i])
			return i;

	return -1;
}
