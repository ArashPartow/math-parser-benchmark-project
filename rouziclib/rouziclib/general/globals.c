framebuffer_t fbs={0};
_Thread_local framebuffer_t *fb=&fbs;
_Thread_local zoom_t zc={0};
mouse_t mouse={0};
vector_font_t *font=NULL;
double drawing_thickness=0.8;
_Thread_local audiosys_t audiosys={0};
_Thread_local window_manager_t wind_man;
