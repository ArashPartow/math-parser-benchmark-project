// in general/textedit_struct.h:
// textedit_t, textundo_t, textundostate_t

extern void textundo_remove_later_states(textedit_t *te);
extern void textundo_clear_all(textedit_t *te);
extern void textundo_free(textedit_t *te);
extern void textundo_add_state(textedit_t *te);
extern void textundo_restore_state(textedit_t *te);
extern void textundo_update(textedit_t *te, int forced_save);
extern void textundo_undo(textedit_t *te);
extern void textundo_redo(textedit_t *te);
