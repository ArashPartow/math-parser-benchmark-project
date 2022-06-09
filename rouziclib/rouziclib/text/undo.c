#define TEXTUNDO_SAVE_DELAY	500	// milliseconds

void textundo_remove_later_states(textedit_t *te)
{
	int i;

	for (i=te->undo.cur_state_index+1; i < te->undo.state_count; i++)
		free(te->undo.state[i].string);

	te->undo.state_count = te->undo.cur_state_index + 1;
}

void textundo_clear_all(textedit_t *te)
{
	int i;

	for (i=0; i < te->undo.state_count; i++)
		free_null(&te->undo.state[i].string);
	free(te->undo.state);

	memset(&te->undo, 0, sizeof(textundo_t));
}

void textundo_free(textedit_t *te)
{
	int i;

	for (i=0; i < te->undo.state_count; i++)
		free (te->undo.state[i].string);

	free (te->undo.state);
	memset(&te->undo, 0, sizeof(textundo_t));
}

void textundo_add_state(textedit_t *te)
{
	textundostate_t *cs;

	if (te->string == NULL)
		return ;

	// Check if the current string is the same as the last undo state
	if (te->undo.state_count > 0 && te->undo.cur_state_index >= 0 && te->undo.cur_state_index < te->undo.state_count)
		if (strcmp(te->string, te->undo.state[te->undo.cur_state_index].string)==0)
			return ;

	textundo_remove_later_states(te);

	alloc_enough(&te->undo.state, te->undo.state_count+=1, &te->undo.alloc_count, sizeof(textundostate_t), 1.5);	// alloc enough space
	te->undo.cur_state_index = te->undo.state_count - 1;

	cs = &te->undo.state[te->undo.cur_state_index];
	cs->string = make_string_copy(te->string);
	cs->alloc_size = strlen(cs->string)+1;
	cs->curpos = te->curpos;
	cs->timestamp = te->undo.timestamp;		// copy the old timestamp which reflects the time of the last change
	te->undo.latest_is_saved = 0;
	te->return_flag = 4;	// indicates modification
}

void textundo_restore_state(textedit_t *te)
{
	textundostate_t *cs;

	te->undo.cur_state_index = MAXN(te->undo.cur_state_index, 0);
	cs = &te->undo.state[te->undo.cur_state_index];

	free (te->string);
	te->string = make_string_copy(cs->string);
	te->alloc_size = cs->alloc_size;
	te->sel0 = te->sel1 = te->curpos = cs->curpos;
	te->return_flag = 4;	// indicates modification
}

void textundo_update(textedit_t *te, int forced_save)
{
	uint32_t timestamp = get_time_ms();

	if (te->undo.alloc_count==0)
	{
		te->undo.state = calloc(te->undo.alloc_count = 16, sizeof(textundostate_t));
		te->undo.cur_state_index = -1;
	}

	if (te->undo.latest_is_saved)
	{
		te->undo.latest_is_saved = 0;
		return ;
	}

	// Save either if the type of change requires it or if it's the first change in a long enough time
	if (forced_save || timestamp - te->undo.timestamp >= TEXTUNDO_SAVE_DELAY)
		textundo_add_state(te);

	te->undo.timestamp = timestamp;

	//for (int i=0; i<te->undo.state_count; i++)
	//	fprintf_rl(stdout, "State #%d: %d B, time %d ms, \"%s\"\n\n", i, te->undo.state[i].alloc_size, timestamp - te->undo.state[i].timestamp, te->undo.state[i].string);
}

void textundo_undo(textedit_t *te)
{
	if (te->undo.alloc_count==0)
		return ;

	if (te->undo.latest_is_saved==0)	// if the latest state hasn't been saved yet
	{
		textundo_update(te, 1);
		te->undo.latest_is_saved = 1;
	}

	te->undo.cur_state_index--;
	textundo_restore_state(te);
}

void textundo_redo(textedit_t *te)
{
	if (te->undo.alloc_count==0)
		return ;

	te->undo.cur_state_index++;
	if (te->undo.state[te->undo.cur_state_index].string == NULL || te->undo.cur_state_index >= te->undo.state_count)
	{
		te->undo.cur_state_index--;
		return ;
	}

	textundo_restore_state(te);
}
