#ifdef RL_VULKAN
// SDL 2 is assumed

#ifdef _MSC_VER
#pragma comment (lib, "vulkan-1.lib")
#endif

extern const char *get_vk_error_string(cl_int err);
extern int vk_create_instance();
extern int vk_pick_physical_device();
extern int vk_init_queue();
extern int vk_init();

#define VK_ERR_RET(name, ret)	if (ret != VK_SUCCESS) { fprintf_rl(stderr, "%s failed (err %d: %s)\n", name, ret, get_vk_error_string(ret));	return ret; }
#define VK_ERR_NORET(name, ret)	if (ret != VK_SUCCESS) { fprintf_rl(stderr, "%s failed (err %d: %s)\n", name, ret, get_vk_error_string(ret));	return ; }

#endif
