extern int unicode_arabic_can_connect(uint32_t c, int next);
extern uint32_t find_arabic_form(uint32_t c, int form_type);
extern uint32_t get_arabic_form(uint32_t c, const uint8_t *string, int len, int prev_con1);
